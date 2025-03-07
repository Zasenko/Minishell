/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 15:40:12 by marvin            #+#    #+#             */
/*   Updated: 2025/02/17 15:40:12 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char *extract_single_string(char *input)
{
    int     i;
    int     len;
    char    *res;

    i = 0;
    len = ft_strlen(input);
    res = (char *)malloc((len - 1) * sizeof(char));
    if (!res)
        return NULL;
    i = 0;
    while (*input)
    {
        if (*input == ' ')
            break;
        if (*input != '\'')
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

void skip_spases(char *input, int *i)
{
    while (input[*i] == 32 || input[*i] == 9)
        (*i)++;
}

char *extract_word(char *input, int *i)
{
    int     start;
    char    *res;

    start = *i;
    while (input[*i] && input[*i] != ' ' && input[*i] != '|' &&
           input[*i] != '<' && input[*i] != '>' && input[*i] != '\t')
        (*i)++;
    res = ft_substr(input, start, *i - start);
    if (!res)
        return NULL;
    return res;
}
int count_quotes(const char *input, char quote) 
{
    int count = 0;
    while (*input) 
    {
        if (*input == quote)
            count++;
        input++;
    }
    return count;
}

bool define_valid_string(char *input) 
{
    int i = 0;
    bool sing_quote = true;
    bool doub_quote = true;

    while (input[i]) 
    {
        if (input[i] == '\"') 
        {
            if (sing_quote) 
                doub_quote = !doub_quote;
        } 
        else if (input[i] == '\'') 
        {
            if (doub_quote)
                sing_quote = !sing_quote;
        }
        i++;
    }
    return (sing_quote && doub_quote);
}
