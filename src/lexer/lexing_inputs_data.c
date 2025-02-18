/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing_inputs_date.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 12:11:16 by marvin            #+#    #+#             */
/*   Updated: 2025/02/12 12:11:16 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool handle_inputs(t_token **head, t_token **token, char *input, int *i)
{
    while (input[*i])
    {
        *token = create_new_token();
        if (!(*token))
            return false;
        skip_spases(input, i);
        if (input[*i] == '\0')
        return false;
        if (input[*i] == '\'')
        {
            if (!handle_single_quote(*token, input, i))
                return false;
        }
        else if (ft_strchr("|<>", input[*i], false))
        {
            if (!handle_operators(*token, input, i))
                return false;
        }
        else if (input[*i] == '$')
        {
            if (!handle_variable(*token, input, i))
                return false;
        }
        else 
            if (!handle_command(*token, last_token_node(*head), input, i))
                return false;
        add_token_back(head, *token);
    }
    return true;
}

void lexing_inputs_data(t_app *shell, char *str)
{
    int i;
    char    *input;
    t_token *head = NULL;
    t_token *token = NULL;

    if (!shell || !str)
        return;
    i = 0;
    if (!handle_duble_quotes(&input, str))
        return;
    if (!handle_inputs(&head, &token, input, &i))
        return;
    free(input);
    shell->tokens = head;
    lexing_checker(shell);
}
