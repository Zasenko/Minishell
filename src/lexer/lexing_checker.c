/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing_checker.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 13:07:47 by marvin            #+#    #+#             */
/*   Updated: 2025/02/17 13:07:47 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool check_pipe(t_token *token)
{
    if (token->type == PIPE)
    {
        if (token->next == NULL || token->prev == NULL 
            ||  token->value == token->next->value  || token->next->type != CMD)
            return false;
    }
    return true;
}

bool check_rederections(t_token *token)
{
    if (token->type == REDIR_IN)
    {
        if (token->next == NULL || token->value == token->next->value
            || token->next->type != ARG )
            return false;
    }
    else if (token->type == REDIR_OUT)
    {
        if (token->next == NULL || token->value == token->next->value
            || token->next->type != ARG)
            return false;
    }
    else if (token->type == APPEND)
    {
        if (token->next == NULL || token->value == token->next->value
            || token->next->type != ARG )
            return false;
    }
    return true;
}

bool lexing_checker(t_app *shell)
{
    t_token *token;

    if (!shell)
        return false;;
    token = shell->tokens;
    while (token != NULL)
    {
        if (!check_pipe(token))
		{
            print_message(PIPE_ERROR, false);
            return false;
        }
        if (!check_rederections(token))
		{
            print_message(REDIR_ERROR, false);
            return false;
        }
        token = token->next;
    }
    return true;
}