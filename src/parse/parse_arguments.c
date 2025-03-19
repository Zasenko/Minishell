/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_arguments.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 16:35:06 by marvin            #+#    #+#             */
/*   Updated: 2025/02/23 16:35:06 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// char **extract_arguments(t_token *token, char *cmd)
// {
//     char    **result;
//     int     args_count;
//     int     i = 0;
    
//     args_count = count_types(token, ARG) + 2;
//     result = (char**)malloc(args_count * sizeof(char*));
//     if (!result)
//         return NULL;
//     while (token && i < args_count - 1)
//     {
//         if (i == 0 && token->type == ARG)
//         {
//             result[i] = ft_strdup(cmd);
//             if (!result[i])
//                 return NULL;
//             i++;
//         }
//         result[i] = ft_strdup(token->value);
//         if (!result[i])
//             return NULL;
//         token = token->next;
//         i++;
//     }
//     result[i] = NULL;
//     return result;
// }

char **create_expanded_args(char *cmd, char *args, int len)
{
    int     i;
    char    **result;

    if (!cmd || !args)
        return NULL;
    i = 0;
    result = (char**)malloc((len + 1) * sizeof(char*));
    while (i < len)
    {
        if (i == 0)
        {
            result[i] = ft_strdup(cmd);
            if (!result[i])
                return (free_2d_array(result), NULL);
        }
        else
        {
            result[i] = ft_strdup(args);
            if (!result[i])
                return (free_2d_array(result), NULL);
        }
        i++;
    }
    result[i] = NULL;
    return result;
}
