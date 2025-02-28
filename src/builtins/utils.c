/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmitryzasenko <dmitryzasenko@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 16:15:41 by dmitryzasen       #+#    #+#             */
/*   Updated: 2025/02/12 16:26:44 by dmitryzasen      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	is_builtin_func(char *cmd)
{

	if (ft_strstr(cmd, "pwd"))
		return (true);
	if (ft_strstr(cmd, "env"))
		return (true);
	if (ft_strstr(cmd, "echo"))
		return (true);
	if (ft_strstr(cmd, "cd"))
		return (true);
	if (ft_strstr(cmd, "exit"))
		return (true);
	if (ft_strstr(cmd, "export"))
		return (true);
	if (ft_strstr(cmd, "unset"))
		return (true);
	else
		return (false);
}

int	exec_buildin(t_cmd *cmd, t_app *shell)
{
	if (ft_strstr(cmd->cmd, "pwd"))
		return (ft_pwd());
	if (ft_strstr(cmd->cmd, "env"))
		return (ft_env(shell->env_var));
	if (ft_strstr(cmd->cmd, "echo"))
		return (ft_echo(cmd->args));
	if (ft_strstr(cmd->cmd, "cd"))
		return (ft_cd(cmd, shell->env_var));
	if (ft_strstr(cmd->cmd, "exit"))
		return (ft_exit(cmd, shell, 0));
	if (ft_strstr(cmd->cmd, "export"))
		return (ft_export(cmd, shell, true));
	if (ft_strstr(cmd->cmd, "unsex"))
		return (ft_unset(cmd, shell, true));
	return (0);
}


bool	ft_strstr(char *str, char *to_find)
{
	int	i;
	int	f;

	if (to_find[0] == '\0')
		return (true);
	i = 0;
	while (str[i] != '\0')
	{
		f = 0;
		while (str[i + f] != '\0' && str[i + f] == to_find[f])
		{
			f++;
			if (to_find[f] == '\0')
				return (true);
		}
		i++;
	}
	return (false);
}
