/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzasenko <dzasenko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 16:49:29 by dmitryzasen       #+#    #+#             */
/*   Updated: 2025/03/07 15:52:31 by dzasenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_execute_command(t_app *shell, t_cmd *cmd)
{
	if (cmd->next != NULL)
	{
		if (pipe(shell->fds.pipe) != 0)
		{
			close_child_fds(shell);
			perror("pipe");
			shell->last_exit_code = errno;
			return (EXIT_FAILURE);
		}
	}
	cmd->pid = fork();
	if (cmd->pid < 0)
	{
		close_child_fds(shell);
		perror("fork");
		shell->last_exit_code = errno;
		return (EXIT_FAILURE);
	}
	if (cmd->pid == 0)
		child_process(shell, cmd);
	close_fd(&shell->fds.pipe[1]);
	close_fd(&shell->fds.prev_pipe);
	shell->fds.prev_pipe = shell->fds.pipe[0];
	shell->fds.pipe[0] = -1;
	return (SUCCESS);
}

int	ft_wait_child(t_cmd *cmd, t_app *shell, int *print_sig_error)
{
	int		status;
	pid_t	child_pid;

	child_pid = waitpid(cmd->pid, &status, 0);
	if (child_pid == -1)
	{
		shell->last_exit_code = errno;
		return (strerror(errno), errno);
	}
	if (WIFEXITED(status))
	{
		shell->last_exit_code = WEXITSTATUS(status);
		return (SUCCESS);
	}
	else if (WIFSIGNALED(status))
	{
		shell->last_exit_code = 128 + WTERMSIG(status);
		if (WTERMSIG(status) == SIGINT)
			*print_sig_error = 2;
		else if (WTERMSIG(status) == SIGQUIT)
			*print_sig_error = 3;
		return (SUCCESS);
	}
	return (SUCCESS);
}

int	ft_wait_children(t_app *shell)
{
	t_cmd	*cmd;
	int		print_sig_error;

	cmd = shell->cmd;
	print_sig_error = 0;
	while (cmd != NULL)
	{
		if (cmd->pid != -1)
			ft_wait_child(cmd, shell, &print_sig_error);
		cmd = cmd->next;
	}
	if (print_sig_error)
	{
		if (print_sig_error == 2)
			printf("\n");
		if (print_sig_error == 3 && shell->last_exit_code == 131)
			printf("Quit (core dumped)\n");
	}
	return (1);
}

void	exe_multi_buildin(t_app *shell, t_cmd *cmd)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	while (cmd != NULL)
	{
		ft_execute_command(shell, cmd);
		cmd = cmd->next;
	}
	ft_wait_children(shell);
	handle_signal_main();
}

int	ft_execute(t_app *shell)
{
	t_cmd	*cmd;
	int		cmd_count;

	cmd_count = cmd_len(shell->cmd);
	if (!cmd_count || !shell->is_valid_syntax)
		return (EXIT_FAILURE);
	if (!make_heredoc(shell))
		return (0);
	handle_signal_main();
	cmd = shell->cmd;
	if (!cmd)
		return (0);
	if (cmd->next == NULL && cmd->args && is_builtin_func(cmd->args[0]))
	{
		if (exe_singl_buildin(shell, cmd) == EXIT_FAILURE)
			return (EXIT_FAILURE);
	}
	else
		exe_multi_buildin(shell, cmd);
	return (SUCCESS);
}
