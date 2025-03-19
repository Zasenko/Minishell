// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   qoute_handler.c                                    :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2025/02/17 14:24:36 by marvin            #+#    #+#             */
// /*   Updated: 2025/02/17 14:24:36 by marvin           ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

#include "../../includes/minishell.h"

// char *extract_duble_string(char *input)
// {
//     int     i;
//     int     len;
//     char    *res;

//     i = 0;
//     len = ft_strlen(input);
//     res = (char *)malloc((len - 1) * sizeof(char));
//     if (!res)
//         return NULL;
//     while (*input)
//     {
//         if (*input != '\"')
//         {
//             res[i] = *input;
//             input++;
//             i++;
//         }
//         else
//             input++;
//     }
//     res[i] = '\0';
//     return res;
// }


bool handle_quotes(t_token *token, t_token *prev, char *input, int *i)
{
    char quote;
    int start;

    start = *i;
    quote = input[*i];
    while (input[*i] && input[*i] != quote)
        (*i)++;
    if (!prev)
        token->type = CMD;
    else
        token->type = ARG;
    token->value = ft_substr(input, start, (*i - start));
    if (!token->value)
        return false;
    return true;
}
