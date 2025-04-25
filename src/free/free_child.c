/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_child.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibondarc <ibondarc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 13:52:33 by dzasenko          #+#    #+#             */
/*   Updated: 2025/04/25 12:27:07 by ibondarc         ###   ########.fr       */
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

void free_cmd_list_child(t_cmd **cmd)
{
    t_cmd *temp;

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
        free_redir_list(&(*cmd)->redirs);
        close_file_descriptors(*cmd);
        free(*cmd);
        *cmd = temp;
    }
    free(*cmd);
    *cmd = NULL;
}

void free_list_in_child(t_app *shell)
{
    if (!shell)
        return ;
    if (shell->env_var)
    {
        free_2d_array(shell->env_var);
        shell->env_var = NULL;
    }
    if (shell->prev_pipe >= 0)
	{
		close(shell->prev_pipe);
		shell->prev_pipe = -1;
	}
    free_prompt(shell);
    free_cmd_list_child(&shell->cmd);
    free_token_list(&shell->tokens); 
}
