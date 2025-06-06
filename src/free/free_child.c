/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_child.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibondarc <ibondarc@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 13:52:33 by dzasenko          #+#    #+#             */
/*   Updated: 2025/05/09 14:42:50 by ibondarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	close_all_redirs_fds_child(t_redir *redir)
{
	t_redir	*temp;

	temp = redir;
	if (!temp)
		return (0);
	while (temp != NULL)
	{
		if (temp->fd > -1)
		{
			close(temp->fd);
			temp->fd = -1;
		}
		temp = temp->next;
	}
	return (1);
}

void	free_cmd_list_child(t_cmd **cmd)
{
	t_cmd	*temp;

	if (!cmd)
		return ;
	while (*cmd != NULL)
	{
		temp = (*cmd)->next;
		if ((*cmd)->cmd)
		{
			free((*cmd)->cmd);
			(*cmd)->cmd = NULL;
		}
		if ((*cmd)->args)
		{
			free_2d_array((*cmd)->args);
			(*cmd)->args = NULL;
		}
		close_all_redirs_fds_child((*cmd)->redirs);
		close_file_descriptors(*cmd);
		free_redir_list(&(*cmd)->redirs);
		free(*cmd);
		*cmd = temp;
	}
	free(*cmd);
	*cmd = NULL;
}

void	free_list_in_child(t_app *shell)
{
	if (!shell)
		return ;
	if (shell->env_var)
	{
		free_2d_array(shell->env_var);
		shell->env_var = NULL;
	}
	free_prompt(shell);
	free_token_list(&shell->tokens);
	free_cmd_list_child(&shell->cmd);
}

void	close_child_fds(t_app *shell)
{
	close_fd(&shell->fds.prev_pipe);
	close_fd(&shell->fds.pipe[0]);
	close_fd(&shell->fds.pipe[1]);
}
