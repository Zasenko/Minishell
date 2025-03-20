/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 12:09:17 by marvin            #+#    #+#             */
/*   Updated: 2025/02/20 12:09:17 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int ft_unset(t_cmd *cmd, t_app *shell, bool is_child)
{
    struct s_envp *envp = shell->envp;
    int i = 1;
    if (is_child)
        return (SUCCESS);

    if (cmd->args[i] == NULL)
    {
        return (SUCCESS);
    }
    else
    {
        while (cmd->args[i])
        {
            t_envp  *node = find_envp_node(envp, cmd->args[i]);
            if (node)
            {
                struct s_envp    *prev = node->prev;
                struct s_envp    *next = node->next;
                if (next)
                {
                    if (prev)
                    {
                        prev->next = next;
                        next->prev = prev;
                    }
                }
                else
                {
                    if (prev)
                    {
                        prev->next = NULL;
                    }
                }
                //delete node
                if (node->envp)
                {
                    free(node->envp);
                }
                if (node->name)
                {
                    free(node->name);
                }
                free(node);
                shell->is_envp_list_changed = true;
            }
            i++;
        }

    }
    return (SUCCESS);
}

void unset_env_values(t_app *shell, t_envp **envp)
{
    t_envp   *curr;
    t_envp   *next;

    t_token *token = shell->tokens;
    while (token)
    {
        if (ft_strncmp(token->value, "unset", 5) == 0)
        {
            curr = *envp;
            while (curr != NULL)
            {
                next = curr->next;
                if (ft_strncmp(curr->name, token->next->value, ft_strlen(token->next->value)) == 0)
                {
                    if (curr->prev)
                        curr->prev->next = next;
                    if (next)
                        next->prev = curr->prev;
                    free(curr->name);
                    free(curr->envp);
                    free(curr);
                }
                curr = next;
            }
        }
        token = token->next;
    }
}