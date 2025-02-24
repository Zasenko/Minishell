/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 16:51:46 by marvin            #+#    #+#             */
/*   Updated: 2025/02/23 16:51:46 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool is_valid_brackets(char *str, char c)
{
    if (!ft_strchr(str, c, false))
        return false;
    return true;
}

char *extract_subcommand(const char *str) 
{
    char *result;
    int start;
    int length;

    start = 0;
    while (str[start] && str[start] != '(')
        start++;
    start++;
    length = ft_strlen(str) - start;
    result = ft_substr(str, start, length - 1);
    if (!result)
        return NULL;
    return result;
}