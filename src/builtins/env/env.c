/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibondarc <ibondarc@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 13:02:48 by dzasenko          #+#    #+#             */
/*   Updated: 2025/05/09 14:36:20 by ibondarc         ###   ########.fr       */
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
