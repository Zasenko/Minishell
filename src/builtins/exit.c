/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 09:59:49 by dzasenko          #+#    #+#             */
/*   Updated: 2025/03/10 18:52:27 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int arr2d_len(char **arr)
{
	int i = 0;
	if (!arr)
		return 0;
	while (arr[i])
		i++;
	return (i);
}

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

void print_exit_error(char *str, bool is_child)
{
	if (!is_child)
		ft_putstr_fd("exit\n", 2);
	ft_putstr_fd("exit: ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(": numeric argument required\n", 2);
}

int ft_exit(t_cmd *cmd, t_app *shell, int is_child)
{
	int args_c;
	char	*trimmed;
	int i = 0;

	args_c = arr2d_len(cmd->args);
	if (args_c == 1)
	{
		if (!is_child)
		{
			ft_putstr_fd("exit\n", 1);
			exit_with_error(shell, shell->last_exit_code, NULL);
		}
		else
			return (shell->last_exit_code);
	}
	trimmed = ft_strtrim(cmd->args[1], " \t");  
	if (!trimmed)
	{
		if (!is_child)
			exit_with_error(shell, 1, MALLOC_FAIL);
		else
			return (1);
	}

	if (trimmed[i] == '+' || trimmed[i] == '-')
		i++;
	if (ft_strlen(&trimmed[i]) < 1)
	{
		print_exit_error(cmd->args[1], !is_child);
		free(trimmed);
		if (!is_child)
			exit_with_error(shell, 2, NULL);
		else
			return (2);
	}
	while (trimmed[i])
	{
		if (!ft_isdigit(trimmed[i]))
		{
			print_exit_error(cmd->args[1], !is_child);
			free(trimmed);
			if (!is_child)
				exit_with_error(shell, 2, NULL);
			else
				return (2);
		}
		i++;
	}
	free(trimmed);
	if (args_c > 2)
	{
		// if (!is_child)
		// 	ft_putstr_fd("exit\n", 2);
		return (ft_putstr_fd("exit: too many arguments\n", 2), 1);
	}

	long long exit_code;
	exit_code = 0;
	int	sign;
	size_t result;
	char    *arg;
	
	arg = cmd->args[1];
	result = 0;
	exit_code = 0;
	sign = my_whitespace(arg, &i);
	while (arg[i] >= 48 && arg[i] <= 57)
	{
		result = result * 10 + (arg[i] - 48);
		if ((sign > 0 && result > LLONG_MAX) || (sign < 0 && result > -(size_t)(LLONG_MIN)))
		{
			print_exit_error(cmd->args[1], !is_child);
			if (!is_child)
				exit_with_error(shell, 2, NULL);
			else
				return (2);
		}
		i++;
	}
	exit_code = (long long)result * sign;
	if (exit_code > 256)
		exit_code = exit_code % 256;
	if (!is_child)
	{
		ft_putstr_fd("exit\n", 1);
		exit_with_error(shell, exit_code, NULL);
	}
	return (exit_code);
}
