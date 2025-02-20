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