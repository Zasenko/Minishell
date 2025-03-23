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

char *extract_quoted_string(char *input, int *i)
{
    char quote = input[*i]; 
    int start = ++(*i); 

    while (input[*i] && input[*i] != quote)
        (*i)++;

    if (input[*i] == quote) 
        (*i)++;

    return strndup(&input[start], (*i - start - 1)); 
}

bool handle_inputs(t_app *shell, t_token **head, t_token **token, char *input)
{
    int     i;
    t_token *last;
    
    i = 0;
    while (input[i])
    {
        *token = create_new_token();
        if (!(*token))
            return false;
        skip_spases(input, &i);
        if (ft_strchr("|<>", input[i], false))
        {
            if (!handle_operators(*token, input, &i))
                return false;
        }
        else 
        {
            last = last_token_node(*head);
            if (last && last->type == HEREDOC)
            {
                int start = i;
                while (input[i] && input[i] != ' ' && input[i] != '|' 
                    && input[i] != '>' && input[i] != '<')
                    i++;
                (*token)->value = ft_substr(input, start, i - start);
                (*token)->type = ARG;
            }
            else if (!handle_command(shell, *token, input, &i))
                return false;
        }
        add_token_back(head, *token);
    }
    return true;
}

void lexing_inputs_data(t_app *shell, char *input)
{
    t_token *head = NULL;
    t_token *token = NULL;
    char    *str;


    if (!shell)
        return;
    str = ft_strtrim(input, " \t");
    if (!define_valid_string(str))
    {
        print_message(QUOTE_ERR, false);
        return;
    }
    if (!handle_inputs(shell, &head, &token, str))
        return;
    free(input);
    shell->tokens = head;
    if (!lexing_checker(shell))
        return;
}
