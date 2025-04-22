/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzasenko <dzasenko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 09:49:08 by dzasenko          #+#    #+#             */
/*   Updated: 2025/02/24 13:00:15 by dzasenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	echo_check_args(char **args, int *i, bool *with_new_line)
{
	int	d;

	while (args[*i])
	{
		if (!ft_strncmp(args[*i], "-n", 2))
		{
			d = 2;
			while (args[*i][d] && args[*i][d] == 'n')
				d++;
			if (args[*i][d] == '\0')
			{
				*with_new_line = false;
				*i = *i + 1;
			}
			else
				break;
		}
		else
			break;
	}
}

int	ft_echo(char **args, int fd)
{
	int		i;
	bool	with_new_line;

	with_new_line = true;
	if (!args || !*args)
		return (ft_putstr_fd("\n", fd), EXIT_SUCCESS);
	i = 1;
	echo_check_args(args, &i, &with_new_line);
	while (args[i])
	{
		ft_putstr_fd(args[i], fd);
		if (args[i + 1] != NULL)
			ft_putstr_fd(" ", fd);
		i++;
	}
	if (with_new_line == true)
		ft_putstr_fd("\n", fd);
	return (EXIT_SUCCESS);
}
