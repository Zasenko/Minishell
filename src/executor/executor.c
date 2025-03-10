/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzasenko <dzasenko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 16:49:29 by dmitryzasen       #+#    #+#             */
/*   Updated: 2025/03/07 14:13:17 by dzasenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	close_all_redirs_fds(t_redir *redir)
{
	t_redir	*temp;

	temp = redir;
	if (!temp)
		return (0);
	while (temp != NULL)
	{
		if (temp->fd != -1)
		{
			close(temp->fd);
		}
		temp = temp->next;
	}
	return (1);
}

int	close_all_cmnds_fds(t_cmd *cmd)
{
	t_cmd	*temp;

	temp = cmd;
	if (!temp)
		return (0);
	while (temp != NULL)
	{
		close_all_redirs_fds(temp->redirs);
		temp = temp->next;
	}
	return (1);
}

int	redirect(t_app *shell, t_cmd *cmd, int prev_pipe, int pipe_fd[2])
{
	(void) shell;
	if (prev_pipe != -1)
	{
		dup2(prev_pipe, 0);
		close(prev_pipe);
	}

	if (cmd->next != NULL)
	{
		dup2(pipe_fd[1], 1);
	}
	
	t_redir *redir = cmd->redirs;
	while (redir)
	{
		if (redir->type == REDIR_IN && redir->fd != -1)
		{
			dup2(redir->fd, 0);
			close(redir->fd);
		}
		if (redir->type == HEREDOC && redir->fd != -1)
		{
			dup2(redir->fd, 0);
			close(redir->fd);
		}	
		if (redir->type == REDIR_OUT && redir->fd != -1)
		{
			dup2(redir->fd, 1);
			close(redir->fd);
		}
		if (redir->type == APPEND && redir->fd != -1)
		{
			dup2(redir->fd, 1);
			close(redir->fd);
		}
		redir = redir->next;
	}

	// if (cmd->fd_in != -1)
	// {
	// 	dup2(cmd->fd_in, 0);
	// 	close(cmd->fd_in);
	// }
	// if (cmd->next != NULL)
	// {
	// 	dup2(pipe_fd[1], 1);
	// }
	// if (cmd->fd_out != -1)
	// {
	// 	dup2(cmd->fd_out, 1);
	// 	close(cmd->fd_out);
	// }

	if (pipe_fd[0] != -1)
		close(pipe_fd[0]);
	if (pipe_fd[1] != -1)
		close(pipe_fd[1]);
	// close_all_cmnds_fds(shell->cmd);
	// close_all_redirs_fds(cmd->redirs);
	return (1);
}

void	child_process(t_app *shell, t_cmd *cmd, int prev_pipe, int pipe_fd[2])
{
	int exit_status;

	redirect(shell, cmd, prev_pipe, pipe_fd);
	close_all_cmnds_fds(shell->cmd);
	if (is_builtin_func(cmd->args[0]))
	{
		exit_status = exec_buildin(cmd, shell);
		free_list(shell);
		exit(exit_status);
	}
	else
	{
		//todo FREE!!!!!
		execve(cmd->args[0], cmd->args, shell->env_var);
		exit_with_error(shell, errno, strerror(errno));
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
	
	// close_all_redirs_fds(cmd->redirs);
	close_all_cmnds_fds(cmd);
	// if (cmd->fd_in != -1)
	// 	close(cmd->fd_in);
	// if (cmd->fd_out != -1)
	// 	close(cmd->fd_out);

	if (*prev_pipe != -1)
		close(*prev_pipe);
	if (pipe_fd[1] != -1)
		close(pipe_fd[1]);
	*prev_pipe = pipe_fd[0];
	return (1);
}

int	ft_wait_child(t_cmd *cmd, t_app *shell)
{
	int		status;
	pid_t	child_pid;

	child_pid = waitpid(cmd->pid, &status, 0);
	if (child_pid == -1)
	{
		shell->last_exit_code = errno;
		return (strerror(errno), errno);
		// printf ("\n\n----ERROR---- %d\n\n", shell->last_exit_code);

	}
	if (WIFEXITED(status))
	{
		shell->last_exit_code = WEXITSTATUS(status);
		// printf ("\n\n-------- %d\n\n", shell->last_exit_code);
		return (SUCCESS);
	}
	return (SUCCESS);
}

int ft_wait_children(t_app *shell)
{
	t_cmd	*cmd;

	cmd = shell->cmd;
	while (cmd != NULL)
	{
		if (cmd->pid != -1)
		{
			ft_wait_child(cmd, shell);
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
	cmd_count = cmd_len(shell->cmd);
	prev_pipe = -1;
	if (!cmd_count)
		return (0);
	while (cmd != NULL)
	{
		// if (cmd->input != NULL)
		// {
		// 	int fd_in = open(cmd->input, O_RDONLY);
		// 	if (fd_in < 0)
		// 	{
		// 		perror("open");
		// 	}
		// 	else
		// 	{
		// 		cmd->fd_in = fd_in;
		// 	}
		// }
		// if (cmd->output != NULL)
		// {
		// 	int fd_out = open(cmd->output, O_WRONLY | O_CREAT |  O_TRUNC, 0644);
		// 	if (fd_out < 0)
		// 	{
		// 		perror("open");
		// 	}
		// 	else
		// 	{
		// 		cmd->fd_out = fd_out;
		// 	}
		// }
		
		t_redir *redir = cmd->redirs;
		while (redir)
		{
			if (redir->type == REDIR_IN)
			{
				printf("REDIR_IN %s\n", redir->value);
				int fd_in = open(redir->value, O_RDONLY);
				if (fd_in < 0)
				{
					perror("open");
				}
				else
				{
					redir->fd = fd_in;
				}
				printf("fd_in %d\n", fd_in);
			}
			if (redir->type == REDIR_OUT)
			{
				printf("REDIR_OUT %s\n", redir->value);
				int fd_out = open(redir->value, O_WRONLY | O_CREAT |  O_TRUNC, 0644);
				if (fd_out < 0)
				{
					perror("open");
				}
				else
				{
					redir->fd = fd_out;
				}
				printf("fd_out %d\n", fd_out);
			}
			if (redir->type == APPEND)
			{
				printf("APPEND %s\n", redir->value);
				int fd_append = open(redir->value, O_WRONLY | O_CREAT | O_APPEND, 0644);
				if (fd_append < 0)
				{
					perror("open");
				}
				else
				{
					redir->fd = fd_append;
				}
				printf("fd_append %d\n", fd_append);
			}
			if (redir->type == HEREDOC)
			{
				printf("HEREDOC %s\n", redir->value);
				if (redir->fd < 0)
				{
					perror("open");
				}
				printf("HEREDOC fd %d\n", redir->fd);
			}
			redir = redir->next;
		}
		cmd = cmd->next;
	}
	cmd = shell->cmd;
	
	if (cmd->next == NULL && !ft_strncmp("cd", cmd->args[0], sizeof(cmd->args[0])))
	{
		shell->last_exit_code = ft_cd(cmd, shell, false);
	}
	else if (cmd->next == NULL &&  !ft_strncmp("exit", cmd->args[0], sizeof(cmd->args[0])))
	{
		ft_exit(cmd, shell, 1);
	}
	else if (cmd->next == NULL && !ft_strncmp("export", cmd->args[0], sizeof(cmd->args[0])))
	{
		shell->last_exit_code = ft_export(cmd, shell, false);
	}
	else if (cmd->next == NULL && !ft_strncmp("unset", cmd->args[0], sizeof(cmd->args[0])))
	{
		shell->last_exit_code = ft_unset(cmd, shell, false);
	}
	else {
		while (cmd != NULL)
		{
			ft_execute_command(shell, cmd, &prev_pipe);
			cmd = cmd->next;
		}
	}

	ft_wait_children(shell);
	
	close_all_cmnds_fds(shell->cmd);
	if (prev_pipe != -1)
		close(prev_pipe);
	return (1);
}