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
        {
            free_2d_array((*cmd)->args);
            (*cmd)->args = NULL;
        }
        close_all_redirs_fds((*cmd)->redirs);
        // if ((*cmd)->cmd) {
        // free((*cmd)->cmd);
        // (*cmd)->cmd = NULL;
        // }
    //    if ((*cmd)->input) {
    //     free((*cmd)->input);
    //     (*cmd)->input = NULL;
    //    }
    //     if ((*cmd)->output) {
    //     free((*cmd)->output);
    //     (*cmd)->output = NULL;
    //     }

        free(*cmd);
        *cmd = temp;
    }
    free(*cmd);
    *cmd = NULL;
}

void free_token_list(t_token **tokens)
{
    t_token *temp;

    if (!tokens)
        return ;
    while (*tokens != NULL)
    {
        temp = (*tokens)->next;
        if ((*tokens)->value)
        {
            free((*tokens)->value);
            (*tokens)->value = NULL;
        }
        free(*tokens);
        *tokens = temp;
    }
    free(*tokens);
    *tokens = NULL;
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
    // if (shell->path)
    //     free_2d_array(shell->path);
    if (shell->env_var)
    {
        free_2d_array(shell->env_var);
        shell->env_var = NULL;
    }
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
    free_token_list(&shell->tokens); 
}
