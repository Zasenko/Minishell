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
