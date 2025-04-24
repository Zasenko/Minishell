/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzasenko <dzasenko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 22:06:59 by dzasenko          #+#    #+#             */
/*   Updated: 2025/04/23 22:06:59 by dzasenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	my_whitespace(const char *str, int *idx)
{
	int	i;
	int	sign;

	i = 0;
	sign = 1;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == 45)
	{
		sign *= -1;
		i++;
	}
	else if (str[i] == 43)
		i++;
	*idx = i;
	return (sign);
}

long long	custom_atoi(t_app *shell, t_cmd *cmd, char *arg, int is_child)
{
	int		i;
	int		sign;
	size_t	res;

	i = 0;
	res = 0;
	sign = my_whitespace(arg, &i);
	while (arg[i] >= 48 && arg[i] <= 57)
	{
		res = res * 10 + (arg[i] - 48);
		if ((sign > 0 && res > LLONG_MAX)
			|| (sign < 0 && res > -(size_t)(LLONG_MIN)))
		{
			print_exit_error(cmd->args[1], !is_child);
			if (!is_child)
				exit_with_error(shell, 2, NULL);
			else
				return (2);
		}
		i++;
	}
	return ((long long)res * sign);
}
