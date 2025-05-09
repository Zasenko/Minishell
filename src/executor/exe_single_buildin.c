/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_single_buildin.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibondarc <ibondarc@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 11:56:07 by dzasenko          #+#    #+#             */
/*   Updated: 2025/05/07 12:13:04 by ibondarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_redir(t_app *shell, t_redir *redir, int *dup_fd, int *fd)
{
	if (redir->fd < 0)
	{
		if (redir->is_ambiguous)
		{
			ft_putstr_fd(redir->err_name, 2);
			ft_putstr_fd(AMBIGOUS_RED, 2);
			shell->last_exit_code = 1;
			return (EXIT_FAILURE);
		}
		print_fd_err(redir->value, strerror(errno));
		shell->last_exit_code = 1;
		return (EXIT_FAILURE);
	}
	close_fd(dup_fd);
	*dup_fd = dup2(redir->fd, *fd);
	if (*dup_fd == -1)
	{
		print_fd_err("dup2", strerror(errno));
		shell->last_exit_code = 1;
		return (EXIT_FAILURE);
	}
	close_fd(&redir->fd);
	return (SUCCESS);
}

int	make_redir_builtin(t_app *shell, t_redir *redir)
{
	if (!redir)
		return (EXIT_FAILURE);
	if (redir->type == REDIR_IN || redir->type == HEREDOC)
	{
		redir->fd = open(redir->value, O_RDONLY);
		if (check_redir(shell, redir, &shell->fds.dup2_in, &shell->fds.pipe[0])
			== EXIT_FAILURE)
			return (EXIT_FAILURE);
	}
	else if (redir->type == REDIR_OUT)
	{
		redir->fd = open(redir->value, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (check_redir(shell, redir, &shell->fds.dup2_out, &shell->fds.pipe[1])
			== EXIT_FAILURE)
			return (EXIT_FAILURE);
	}
	else if (redir->type == APPEND)
	{
		redir->fd = open(redir->value, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (check_redir(shell, redir, &shell->fds.dup2_out, &shell->fds.pipe[1])
			== EXIT_FAILURE)
			return (EXIT_FAILURE);
	}
	return (SUCCESS);
}

int	exe_singl_buildin(t_app *shell, t_cmd *cmd)
{
	t_redir	*redir;

	shell->fds.pipe[0] = dup(0);
	shell->fds.pipe[1] = dup(1);
	redir = cmd->redirs;
	while (redir)
	{
		if (make_redir_builtin(shell, redir) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		redir = redir->next;
	}
	shell->last_exit_code = exec_buildin(cmd, shell, false, shell->fds.pipe[1]);
	return (SUCCESS);
}
