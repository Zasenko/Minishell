/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 22:05:24 by marvin            #+#    #+#             */
/*   Updated: 2025/04/23 22:05:24 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int hadle_checking_digit(char *trimmed, char *arg, int is_child, int *i)
{
	while (trimmed[*i])
	{
		if (!ft_isdigit(trimmed[*i]))
		{
			print_exit_error(arg, !is_child);
			return (2);
		}
		(*i)++;
	}
	return 0;
}

int check_is_digits(t_app *shell, char *arg, int is_child, int *i)
{
	char	*trimmed;

	trimmed = ft_strtrim(arg, " \t");  
	if (!trimmed)
	{
		if (!is_child)
			exit_with_error(shell, 1, MALLOC_FAIL);
		else
			return (1);
	}
	if (trimmed[*i] == '+' || trimmed[*i] == '-')
		(*i)++;
	if (ft_strlen(&trimmed[*i]) < 1)
	{
		print_exit_error(arg, !is_child);
		return (free(trimmed), 2);
	}
	if (hadle_checking_digit(trimmed, arg, is_child, i))
		return (free(trimmed), 2);
	return (free(trimmed), 0);
}

int validate_input_arguments(t_app *shell, t_cmd *cmd, int args_c, int is_child)
{
	int i;
	int res;

	i = 0;
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
	else
	{
		res = check_is_digits(shell, cmd->args[1], is_child, &i);
		if (res && is_child)
			return res;
		else if (res == 2 && !is_child)
			exit_with_error(shell, 2, NULL);
	}
	return 0;
}