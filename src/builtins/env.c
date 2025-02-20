/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzasenko <dzasenko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 13:02:48 by dzasenko          #+#    #+#             */
/*   Updated: 2025/02/19 13:10:01 by dzasenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int ft_env(char **env)
{
    int i;

    if (!env)
        return (0);
    i = 0;
    while (env[i])
    {
        printf("%s\n", env[i]);
        i++;
    }
    return (1);
}
