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
    res = ft_substr(input, start, *i - start);
    if (!res)
        return NULL;
    return res;
}