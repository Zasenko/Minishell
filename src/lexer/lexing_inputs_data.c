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

void skip_spases(char *input, int *i)
{
    while (input[*i] == 32 || input[*i] == 9)
        (*i)++;
}



bool define_valid_string(char *input)
{
    char    quote;
    int     quote_count;
    int     i;

    i = 0;
    quote_count = 0;
    while (input[i] && input[i] != '\"' && input[i] != '\'')
        i++;
    quote = input[i];
    while (*input)
    {
        if (*input == quote)
            quote_count++;
        input++;
    }
    if (quote_count % 2 != 0)
        return false;
    return true;
}

char *extract_string(char *input, int *i)
{
    char    quote;
    int     start;
    char    *res;

    quote = input[*i];
    start = ++(*i);
    while (input[*i] && input[*i] != quote)
        (*i)++;
    if (input[*i] == quote)
        (*i)++;
    res = ft_substr(input, start, *i - start - 1);
    if (!res)
        return NULL;
    return res;
}

char *extract_duble_string(char *input)
{
    int     i;
    int     len;
    char    *res;

    i = 0;
    len = ft_strlen(input);
    res = (char *)malloc((len - 1) * sizeof(char));
    if (!res)
        return NULL;
    while (*input)
    {
        if (*input != '\"')
        {
            res[i] = *input;
            input++;
            i++;
        }
        else
            input++;
    }
    res[i] = '\0';
    return res;
}



t_type define_operator(char *input, int *i)
{
    if (input[*i] == '|')
        return PIPE;
    if (input[*i] == '<')
    {
        if (input[*i + 1] == '<')
            return HEREDOC;
        else
            return REDIR_IN;
    }
    if (input[*i] == '>')
    {
        if (input[*i + 1] == '>')
            return APPEND;
        else
            return REDIR_OUT;
    }
    return ERROR;
}

char *extract_word(char *input, int *i)
{
    int     start;
    char    *res;

    start = *i;
    while (input[*i] && input[*i] != ' ' && input[*i] != '|' &&
           input[*i] != '<' && input[*i] != '>')
        (*i)++;
    res = ft_substr(input, start, *i - start);
    if (!res)
        return NULL;
    return res;
}

bool lexing_inputs_data(t_app *shell, char *input)
{
    int i;
    char    *value;
    t_type  type;
    bool    redir = false;
    bool    cmd_exist = true;

    if (!input)
        return false;
    if (!define_valid_string(input))
        return false;
    if (ft_strchr(input, '\"', false))
        input = extract_duble_string(input);
    while (input[i])
    {
        skip_spases(input, &i);
        if (input[i] == '\0')
            break;
        if (input[i] == '\'')
        {
           
            type = QUOTE;
            value = extract_string(input, &i);
            if (!value)
                return false;
            
        }
        else if (ft_strchr("|<>", input[i], false))
        {
            type = define_operator(input, &i);
            value = ft_substr(input, i++, 1);
            if (!value)
                return false;
            if (type == REDIR_OUT)
                redir = true;
            cmd_exist = true;
        }
        else if (input[i] == '$')
        {
            type = VAR;
            value = extract_word(input, &i);
            if (!value)
                return false;
        }
        else
        {
            value = extract_word(input, &i);
            if (!value)
                return false;
            skip_spases(input, &i);
            if (input[i] == '<' || input[i + 1] == '<')
                type = IN_FILE;
            else if (redir)
                type = OUT_FILE;
            else 
            { 
                if (cmd_exist)
                {
                    type = CMD;
                    cmd_exist = false;
                }
                else
                    type = ARG;
            }
        }
        add_token_back(&shell->tokens, create_new_token(value, type));
    }    
    return true;    
}