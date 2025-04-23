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

int ft_exit(t_cmd *cmd, t_app *shell, int is_parent)
{
	if (is_parent)
		ft_putstr_fd("exit\n", 1);
    
    if (arr2d_len(cmd->args) == 1)
    {
        if (is_parent)
			exit_with_error(shell, shell->last_exit_code, NULL);
        else
            return (shell->last_exit_code);
    }
    int f = 1;
    while (cmd->args[f])
    {
        if (f == 2)
        {
            if (arr2d_len(cmd->args) > 2)
                return (ft_putstr_fd("exit: too many arguments\n", 2), 1);
        }

        char *trimmed = ft_strtrim(cmd->args[f], " \t");  
        if (!trimmed)
        {
            if (is_parent)
                exit_with_error(shell, 1, NULL);
            else
				return (1);
        }
        int i = 0;
        if (trimmed[i] == '+' || trimmed[i] == '-')
            i++;
        if (ft_strlen(&trimmed[i]) < 1)
        {
            ft_putstr_fd("exit: ", 2);
            ft_putstr_fd(cmd->args[f], 2);
            ft_putstr_fd(": numeric argument required\n", 2);
            free(trimmed);
            if (is_parent)
				exit_with_error(shell, 2, NULL);
            else
                return (2);
        }

        while (trimmed[i])
        {
            if (!ft_isdigit(trimmed[i]))
            {
                ft_putstr_fd("exit: ", 2);
                ft_putstr_fd(cmd->args[f], 2);
                ft_putstr_fd(": numeric argument required\n", 2);
                free(trimmed);
                if (is_parent)
                    exit_with_error(shell, 2, NULL);
                else
                    return (2);
            }
            i++;
        }
        free(trimmed);
        f++;
    }

    f = 1;
    long long exit_code = 0;
    while (cmd->args[f])
    {

        int	i;
	    int	sign;
	    size_t result;
        char    *arg;
        
        arg = cmd->args[f];
	    result = 0;
        exit_code = 0;
	    sign = my_whitespace(arg, &i);
	    while (arg[i] >= 48 && arg[i] <= 57)
	    {
	    	result = result * 10 + (arg[i] - 48);
            if ((sign > 0 && result > LLONG_MAX) || (sign < 0 && result > -(size_t)(LLONG_MIN)))
            {
                ft_putstr_fd("exit: ", 2);
                ft_putstr_fd(cmd->args[1], 2);
                ft_putstr_fd(": numeric argument required\n", 2);
                if (is_parent)
                    exit_with_error(shell, 2, NULL);
                else
                    return (2);
            }
	    	i++;
	    }
        exit_code = (long long)result * sign;
        f++;
    }
    if (is_parent)
		exit_with_error(shell, exit_code, NULL);
	return (exit_code);
}