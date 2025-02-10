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
            free_2d_array((*cmd)->args);
        free(*cmd);
        *cmd = temp;
    }
    free(*cmd);
    *cmd = NULL;
}

void free_envp_list(t_envp **envp)
{
    t_envp *temp;

    if (!envp)
        return ;
    while (*envp != NULL)
    {
        temp = (*envp)->next;
        free((*envp)->name);
        free((*envp)->envp);
        free(*envp);
        *envp = temp;
    }
    free(*envp);
    *envp = NULL;
}

void free_list(t_app *shell)
{
    if (!shell)
        return ;
    if (shell->path)
        free_2d_array(shell->path);
    if (shell->user)
        free(shell->user);
    if (shell->name)  
        free(shell->name);
    if (shell->pwd)
        free(shell->pwd);
    if (shell->prompt)
        free(shell->prompt);
    free_cmd_list(&shell->cmd);
    free_envp_list(&shell->envp);
}
