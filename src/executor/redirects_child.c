/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects_child.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzasenko <dzasenko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 10:05:00 by dzasenko          #+#    #+#             */
/*   Updated: 2025/05/06 14:55:12 by dzasenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	do_dup2(t_app *shell, int *dup_fd, int *fd, int in_out_fd)
{
	close_fd(dup_fd);
	*dup_fd = dup2(*fd, in_out_fd);
	if (*dup_fd == -1)
		exit_child(shell, 1, NULL);
	close_fd(fd);
}

void	make_child_redir_in_heredoc(t_app *shell, t_redir *redir)
{
	redir->fd = open(redir->value, O_RDONLY, 0644);
	if (redir->fd < 0)
	{
		print_fd_err(redir->value, strerror(errno));
		exit_child(shell, 1, NULL);
	}
	do_dup2(shell, &shell->fds.dup2_in, &redir->fd, 0);
}

void	make_child_redir_out(t_app *shell, t_redir *redir)
{
	redir->fd = open(redir->value, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (redir->fd < 0)
	{
		print_fd_err(redir->value, strerror(errno));
		exit_child(shell, 1, NULL);
	}
	do_dup2(shell, &shell->fds.dup2_out, &redir->fd, 1);
}

void	make_child_redir_append(t_app *shell, t_redir *redir)
{
	redir->fd = open(redir->value, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (redir->fd < 0)
	{
		print_fd_err(redir->value, strerror(errno));
		exit_child(shell, 1, NULL);
	}
	do_dup2(shell, &shell->fds.dup2_out, &redir->fd, 1);
}

void	redirects_in_child(t_app *shell, t_cmd *cmd)
{
	t_redir	*redir;

	if (shell->fds.prev_pipe != -1)
		do_dup2(shell, &shell->fds.dup2_in, &shell->fds.prev_pipe, 0);
	if (cmd->next != NULL)
		do_dup2(shell, &shell->fds.dup2_out, &shell->fds.pipe[1], 1);
	redir = cmd->redirs;
	while (redir)
	{
		if (redir->type == REDIR_IN || redir->type == HEREDOC)
			make_child_redir_in_heredoc(shell, redir);
		else if (redir->type == REDIR_OUT)
			make_child_redir_out(shell, redir);
		else if (redir->type == APPEND)
			make_child_redir_append(shell, redir);
		redir = redir->next;
	}
	close_child_fds(shell);
}
