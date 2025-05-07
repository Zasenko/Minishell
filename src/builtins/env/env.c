/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzasenko <dzasenko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 13:02:48 by dzasenko          #+#    #+#             */
/*   Updated: 2025/05/07 17:04:05 by dzasenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	ft_env(char **env)
{
	int	i;

	if (!env)
		return (EXIT_FAILURE);
	i = 0;
	while (env[i])
	{
		if (ft_strchr(env[i], '=', false))
		{
			ft_putstr_fd(env[i], 1);
			ft_putstr_fd("\n", 1);	
		}
		i++;
	}
	return (EXIT_SUCCESS);
}
