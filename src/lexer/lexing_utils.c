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

bool count_quotes(char *input)
{
    int i = 0;
    int quotes = 0;

    if (!input)
        return 0;
    while (input[i])
    {
        if (input[i] == '\'')
            quotes++;
        i++;
    }
    if (quotes % 2 != 0)
        return false;
    return true;
}

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
           input[*i] != '<' && input[*i] != '>')
        (*i)++;
    int j = start;
    while (j < *i)
    {
        if (input[j] == '\'' && count_quotes(input))
        {
            res = extract_single_string(&input[start]);
            if (!res)
                return NULL;
            return res;
        }
        j++;
    }
    res = ft_substr(input, start, *i - start);
    if (!res)
        return NULL;
    return res;
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