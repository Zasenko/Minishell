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

	if (!cmd)
		return false;

	if (!ft_strncmp("pwd", cmd, ft_strlen(cmd)))
		return (true);
	if (!ft_strncmp("env", cmd, ft_strlen(cmd)))
		return (true);
	if (!ft_strncmp("echo", cmd, ft_strlen(cmd)))
		return (true);
	if (!ft_strncmp("cd", cmd, ft_strlen(cmd)))
		return (true);
	if (!ft_strncmp("exit", cmd, ft_strlen(cmd)))
		return (true);
	if (!ft_strncmp("export", cmd, ft_strlen(cmd)))
		return (true);
	if (!ft_strncmp("unset", cmd, ft_strlen(cmd)))
		return (true);
	else
		return (false);
}

int	exec_buildin(t_cmd *cmd, t_app *shell, bool is_child, int fd)
{
	// signal(SIGPIPE, SIG_IGN);
	if (ft_strstr(cmd->args[0], "pwd"))
		return (ft_pwd());
	if (ft_strstr(cmd->args[0], "env"))
		return (ft_env(shell->env_var));
	if (ft_strstr(cmd->args[0], "echo"))
		return (ft_echo(cmd->args, fd));
	if (ft_strstr(cmd->args[0], "cd"))
		return (ft_cd(cmd, shell, is_child));
	if (ft_strstr(cmd->args[0], "exit"))
		return (ft_exit(cmd, shell, 0));
	if (ft_strstr(cmd->args[0], "export"))
		return (ft_export(cmd, shell, is_child));
	if (ft_strstr(cmd->args[0], "unset"))
		return (ft_unset(cmd, shell, is_child));
	return (EXIT_FAILURE);
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
