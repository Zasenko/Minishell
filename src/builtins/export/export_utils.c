/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibondarc <ibondarc@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 13:23:25 by ibondarc          #+#    #+#             */
/*   Updated: 2025/04/29 14:03:05 by ibondarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int check_export_key(char *str)
{
    int i = 0;
    int len = ft_strlen(str);
    if (len == 0 || (len == 1 && !ft_isalpha(str[i])))
    {
        return (0);
    }
    else {
        while (str[i])
        {
            if (!ft_isprint(str[i]))
            {
                return (0);
            }
            else if (i == 0 && (!ft_isalpha(str[i]) && str[i] != '_'))
            {
                return (0);
            }
            else if (!ft_isalnum(str[i]) && str[i] != '_')
            {
                return (0);
            }
            i++;
        }   
    }
    return (1);
}

void    sort_2d_env(char **env)
{
    int     i;
    int     sorted;
    char    *tmp;

    if (!env)
        return;
    sorted = 0;
    while (!sorted)
    {
        i = 0;
        sorted = 1;
        while (env[i] && env[i + 1])
        {
            if (ft_strcmp(env[i], env[i + 1]) > 0)
            {
                tmp = env[i];
                env[i] = env[i + 1];
                env[i + 1] = tmp;
                sorted = 0;
            }
            i++;
        }
    }
}
