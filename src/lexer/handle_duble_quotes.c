/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   qoute_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 14:24:36 by marvin            #+#    #+#             */
/*   Updated: 2025/02/17 14:24:36 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

bool handle_duble_quotes(char **des, char *input)
{
    if (!define_valid_string(input))
        return false;
    if (ft_strchr(input, '\"', false))
    {
        *des = extract_duble_string(input);
        if (!(*des))
            return false;
    }
    else
    {
        *des = ft_strdup(input);
        if (!(*des))
            return false;
    }
    free(input);
    return true;
}
