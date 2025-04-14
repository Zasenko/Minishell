/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibondarc <ibondarc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 13:02:48 by dzasenko          #+#    #+#             */
/*   Updated: 2025/04/14 11:56:25 by ibondarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int ft_env(char **env)
{
    int i;

    if (!env)
        return (EXIT_FAILURE);
    i = 0;
    while (env[i])
    {
        printf("%s\n", env[i]);
        i++;
    }
    return (EXIT_SUCCESS);
}
