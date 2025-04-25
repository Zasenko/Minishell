/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_single_buildin.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzasenko <dzasenko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 11:56:07 by dzasenko          #+#    #+#             */
/*   Updated: 2025/04/25 12:35:07 by dzasenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int exe_singl_buildin(t_app *shell, t_cmd *cmd)
{
	shell->dup_fd[0] = dup(0);
	shell->dup_fd[1] = dup(1);
	t_redir *redir = cmd->redirs;
    
	while (redir)
	{
		if (redir->type == REDIR_IN || redir->type == HEREDOC)
		{
			redir->fd = open(redir->value, O_RDONLY);
			if (redir->fd < 0)
			{
				print_fd_err(redir->value, strerror(errno));
				shell->last_exit_code = 1;
				close(shell->dup_fd[0]);
                shell->dup_fd[0] = -1;
				close(shell->dup_fd[1]);
                shell->dup_fd[1] = -1;
				return (EXIT_FAILURE);
			}
			dup2(redir->fd, shell->dup_fd[0]);
			close(redir->fd);
            redir->fd = -1;
		} 
		else if (redir->type == REDIR_OUT)
		{
			redir->fd = open(redir->value, O_WRONLY | O_CREAT |  O_TRUNC, 0644);
			if (redir->fd < 0)
			{
				close(shell->dup_fd[0]);
                shell->dup_fd[1] = -1;
				close(shell->dup_fd[1]);
                shell->dup_fd[1] = -1;
				print_fd_err(redir->value, strerror(errno));
				return (EXIT_FAILURE);
			}
			dup2(redir->fd, shell->dup_fd[1]);
			close(redir->fd);
            redir->fd = -1;
		} 
		else if (redir->type == APPEND)
		{
			redir->fd = open(redir->value, O_WRONLY | O_CREAT | O_APPEND, 0644);
			if (redir->fd < 0)
			{
				close(shell->dup_fd[0]);
                shell->dup_fd[0] = -1;
				close(shell->dup_fd[1]);
                shell->dup_fd[1] = -1;
				print_fd_err(redir->value, strerror(errno));
				return (EXIT_FAILURE);
			}
			dup2(redir->fd, shell->dup_fd[1]);
			close(redir->fd);
		}
		redir = redir->next;
	}
	shell->last_exit_code = exec_buildin(cmd, shell, false, shell->dup_fd[1]);
    
	if(shell->dup_fd[0] != -1)
	{
		close(shell->dup_fd[0]);
		shell->dup_fd[0] = -1;
	}
	if(shell->dup_fd[1] != -1)
	{
		close(shell->dup_fd[1]);
		shell->dup_fd[1] = -1;
	}
    
    return (SUCCESS);
}
