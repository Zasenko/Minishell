/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_single_buildin.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzasenko <dzasenko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 11:56:07 by dzasenko          #+#    #+#             */
/*   Updated: 2025/04/29 11:29:54 by dzasenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void close_fd(int *fd)
{
	if(fd && *fd != -1)
	{
		close(*fd);
		*fd = -1;
	}
}

void close_dup_fds(t_app *shell)
{
	close_fd(&shell->dup_fd[0]);
	close_fd(&shell->dup_fd[1]);
}

int	exe_singl_buildin(t_app *shell, t_cmd *cmd)
{
	t_redir	*redir;
	
	shell->dup_fd[0] = dup(0);
	shell->dup_fd[1] = dup(1);
	redir = cmd->redirs;
	while (redir)
	{
		if (redir->type == REDIR_IN || redir->type == HEREDOC)
		{
			redir->fd = open(redir->value, O_RDONLY);
			if (redir->fd < 0)
			{
				print_fd_err(redir->value, strerror(errno));
				shell->last_exit_code = 1;
				close_dup_fds(shell);
				return (EXIT_FAILURE);
			}
			dup2(redir->fd, shell->dup_fd[0]);
			close_fd(&redir->fd);
		}
		else if (redir->type == REDIR_OUT)
		{
			redir->fd = open(redir->value, O_WRONLY | O_CREAT |  O_TRUNC, 0644);
			if (redir->fd < 0)
			{
				close_dup_fds(shell);
				print_fd_err(redir->value, strerror(errno));
				return (EXIT_FAILURE);
			}
			dup2(redir->fd, shell->dup_fd[1]);
			close_fd(&redir->fd);
		} 
		else if (redir->type == APPEND)
		{
			redir->fd = open(redir->value, O_WRONLY | O_CREAT | O_APPEND, 0644);
			if (redir->fd < 0)
			{
				close_dup_fds(shell);
				print_fd_err(redir->value, strerror(errno));
				return (EXIT_FAILURE);
			}
			dup2(redir->fd, shell->dup_fd[1]);
			close_fd(&redir->fd);
		}
		redir = redir->next;
	}
	shell->last_exit_code = exec_buildin(cmd, shell, false, shell->dup_fd[1]);
	close_dup_fds(shell);
	return (SUCCESS);
}
