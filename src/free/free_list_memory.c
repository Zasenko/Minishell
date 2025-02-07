/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_list_memory.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 12:19:35 by marvin            #+#    #+#             */
/*   Updated: 2025/02/05 12:19:35 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void free_cmd_list(t_cmd **cmd)
{
    t_cmd *temp;

    if (!cmd)
        return ;
    while (*cmd != NULL)
    {
        temp = (*cmd)->next;
        if ((*cmd)->args)
            free_allocated_memory((*cmd)->args);
        free(*cmd);
        *cmd = temp;
    }
    free(*cmd);
    *cmd = NULL;
}

void free_list(t_app *shell)
{
    if (!shell)
        return ;
    if (shell->path)
        free_allocated_memory(shell->path);
    if (shell->user)
    {
        free(shell->user);
        shell->user = NULL;
    }
    if (shell->name)  
    {   
        free(shell->name);
        shell->name = NULL;
    }
    if (shell->pwd)
    {
        free(shell->pwd);
        shell->pwd = NULL;
    }
    if (shell->prompt)
    {
        free(shell->prompt);
        shell->prompt = NULL;
    }
    free_cmd_list(&shell->cmd);
}
