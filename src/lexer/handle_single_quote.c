/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_single_quote.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 15:04:46 by marvin            #+#    #+#             */
/*   Updated: 2025/02/17 15:04:46 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char *extract_string(char *input, int *i)
{
    char    quote;
    int     start;
    char    *res;

    if (!input[*i])
        return NULL;
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

bool handle_single_quote(t_token *token, char *input, int *i)
{
    token->type = ARG;
    token->value = extract_string(input, i);
    if (!token->value)
        return NULL;
    return true;
}