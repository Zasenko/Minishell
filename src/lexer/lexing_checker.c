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
            || token->next->type != IN_FILE )
            return false;
    }
    else if (token->type == REDIR_OUT)
    {
        if (token->next == NULL || token->value == token->next->value
            || token->next->type != OUT_FILE)
            return false;
    }
    else if (token->type == APPEND)
    {
        if (token->next == NULL || token->value == token->next->value
            || token->next->type != OUT_FILE )
            return false;
    }
    return true;
}

void lexing_checker(t_app *shell)
{
    t_token *token;

    if (!shell)
        exit_with_error(shell, 1);
    token = shell->tokens;
    while (token != NULL)
    {
        if (!check_pipe(token))
		{
            printf("%s %s %s\n", RED, "There is an error of count '|' value!", RESET);
            // exit_with_error(shell, 1);
        }
        if (!check_rederections(token))
		{
            printf("%s %s %c%s%c %s %s\n", RED, "There is an error of count", '\'',
                token->value,'\'', "value!", RESET);
            // exit_with_error(shell, 1);
        }
        token = token->next;
    }
}