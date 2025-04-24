/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzasenko <dzasenko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 09:59:49 by dzasenko          #+#    #+#             */
/*   Updated: 2025/03/10 18:52:27 by dzasenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	arr2d_len(char **arr)
{
	int	i;

	i = 0;
	if (!arr)
		return (0);
	while (arr[i])
		i++;
	return (i);
}

void	print_exit_error(char *str, bool is_child)
{
	if (!is_child)
		ft_putstr_fd("exit\n", 2);
	ft_putstr_fd("exit: ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(": numeric argument required\n", 2);
}

int	ft_exit(t_cmd *cmd, t_app *shell, int is_child)
{
	int			res;
	int			args_c;
	long long	exit_code;

	args_c = arr2d_len(cmd->args);
	res = validate_input_arguments(shell, cmd, args_c, is_child);
	if (res)
		return (res);
	if (args_c > 2)
	{
		// if (!is_child)
		// 	ft_putstr_fd("exit\n", 2);
		return (ft_putstr_fd("exit: too many arguments\n", 2), 1);
	}
	exit_code = custom_atoi(shell, cmd, cmd->args[1], is_child);
	if (exit_code > 256)
		exit_code = exit_code % 256;
	if (!is_child)
	{
		ft_putstr_fd("exit\n", 1);
		exit_with_error(shell, exit_code, NULL);
	}
	return (exit_code);
}
