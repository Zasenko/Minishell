/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzasenko <dzasenko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 16:49:29 by dmitryzasen       #+#    #+#             */
/*   Updated: 2025/02/18 12:05:35 by dzasenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	close_all_cmnds_fds(t_cmd *cmd)
{
	t_cmd	*temp;

	temp = cmd;
	if (!temp)
		return (0);
	while (temp != NULL)
	{
		if (temp->fd_in != -1)
		{
			close(temp->fd_in);
		}
		if (temp->fd_out != -1)
		{
			close(temp->fd_out);
		}
		temp = temp->next;
	}
	return (1);
}

int	redirect(t_app *shell, t_cmd *cmd, int prev_pipe, int pipe_fd[2])
{
	if (prev_pipe != -1)
	{
		dup2(prev_pipe, 0);
		close(prev_pipe);
	}
	if (cmd->fd_in != -1)
	{
		dup2(cmd->fd_in, 0);
		close(cmd->fd_in);
	}
	if (cmd->fd_out != -1)
	{
		dup2(cmd->fd_out, 1);
		close(cmd->fd_out);
	}
	if (cmd->next != NULL)
	{
		dup2(pipe_fd[1], 1);
	}
	if (pipe_fd[0] != -1)
		close(pipe_fd[0]);
	if (pipe_fd[1] != -1)
		close(pipe_fd[1]);
	close_all_cmnds_fds(shell->cmd);
	return (1);
}

void	child_process(t_app *shell, t_cmd *cmd, int prev_pipe, int pipe_fd[2])
{
	redirect(shell, cmd, prev_pipe, pipe_fd);
	if (is_builtin_func(cmd->cmd))
	{
		if (!exec_buildin(cmd))
			exit(EXIT_FAILURE);
		else
			exit(EXIT_SUCCESS);
	}
	else
	{
		if (execve(cmd->cmd, cmd->args, shell->env_var) != 0)
		{
			perror("execve");
			exit(EXIT_FAILURE);
		}
	}
}

int	ft_execute_command(t_app *shell, t_cmd *cmd, int *prev_pipe)
{
	int	pipe_fd[2];

	pipe_fd[0] = -1;
	pipe_fd[1] = -1;
	if (cmd->next != NULL)
	{
		if (pipe(pipe_fd) != 0)
		{
			// check
			perror("pipe");
			return (0); // todo? break and waitpid?
		}
	}
	cmd->pid = fork();
	if (cmd->pid < 0)
	{
		perror("fork");
		return (0); // todo? break and waitpid?
	}

	
	// child
	if (cmd->pid == 0)
		child_process(shell, cmd, *prev_pipe, pipe_fd);

	if (*prev_pipe != -1)
		close(*prev_pipe);
	if (pipe_fd[1] != -1)
		close(pipe_fd[1]);
	*prev_pipe = pipe_fd[0];
	return (1);
}

int	ft_wait_child(t_cmd *cmd)
{
	int		status;
	pid_t	child_pid;

	child_pid = waitpid(cmd->pid, &status, 0);
	if (child_pid == -1)
		return (perror("waitpid"), 0);
	if (WIFEXITED(status))
	{
		if (WEXITSTATUS(status) == EXIT_FAILURE)
			return (0);
	}
	return (1);
}

int ft_wait_children(t_app *shell)
{
	t_cmd	*cmd;

	cmd = shell->cmd;
	while (cmd != NULL)
	{
		if (cmd->pid != -1)
		{
			ft_wait_child(cmd);
		}
		cmd = cmd->next;
	}
	return (1);
}

int	ft_execute(t_app *shell)
{
	t_cmd	*cmd;
	int		cmd_count;
	int		prev_pipe;

	cmd = shell->cmd;
	cmd_count = cmd_len(cmd);
	prev_pipe = -1;
	if (!cmd_count)
		return (0);
	while (cmd != NULL)
	{
		ft_execute_command(shell, cmd, &prev_pipe);
		cmd = cmd->next;
	}
	ft_wait_children(shell);
	close_all_cmnds_fds(shell->cmd);
	if (prev_pipe != -1)
		close(prev_pipe);
	return (1);
}
