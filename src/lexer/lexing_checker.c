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

bool check_pipe(t_app *shell, t_token *token)
{
    if (token->type == PIPE)
    {
        if (!token->prev)
        {
            ft_putstr_fd("syntax error near unexpected token `", 2);
            ft_putstr_fd(token->value, 2);
            ft_putstr_fd("'\n", 2);
            shell->last_exit_code = 2;
            return false;
        }
        else if (token->next == NULL || token->type == token->next->type)
        {
            ft_putstr_fd("syntax error near unexpected token `", 2);
            if (token->next)
                ft_putstr_fd(token->next->value, 2);
            ft_putstr_fd("'\n", 2);
            shell->last_exit_code = 2;
            return false;
        }
    }
    return true;
}

bool check_rederections(t_app *shell, t_token *token)
{
    if (token->type == REDIR_IN || token->type == REDIR_OUT 
        || token->type == APPEND || token->type == HEREDOC)
    {
        if (token->next == NULL)
        {
            ft_putstr_fd("syntax error near unexpected token `newline", 2);
            ft_putstr_fd("'\n", 2);
            shell->last_exit_code = 2;
            return false;
        }
        else if (token->value == token->next->value || token->next->type != ARG )
        {
            ft_putstr_fd("syntax error near unexpected token `", 2);
            if (token->next)
                ft_putstr_fd(token->next->value, 2);
            ft_putstr_fd("'\n", 2);
            shell->last_exit_code = 2;
            return false;
        }
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
        if (!check_pipe(shell, token))
		{
            return false;
        }
        if (!check_rederections(shell, token))
		{
            return false;
        }
        token = token->next;
    }
    return true;
}