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
	if (!ft_strcmp("pwd", cmd))
		return (true);
	if (!ft_strcmp("env", cmd))
		return (true);
	if (!ft_strcmp("echo", cmd))
		return (true);
	if (!ft_strcmp("cd", cmd))
		return (true);
	if (!ft_strcmp("exit", cmd))
		return (true);
	if (!ft_strcmp("export", cmd))
		return (true);
	if (!ft_strcmp("unset", cmd))
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
		return (ft_exit(cmd, shell, is_child));
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

void sort_environment(t_envp **envp)
{
	t_envp *curr;
	t_envp *temp1;
	t_envp *temp2;
	bool swapped;

	if (!envp || !(*envp)) 
		return;
	while (1)
	{
		swapped = true;
		curr = *envp;

		while (curr->next)
		{
			if (ft_strcmp(curr->name, curr->next->name) > 0)
			{
				temp1 = curr;
				temp2 = curr->next;
				temp1->next = temp2->next;
				if (temp2->next)
					temp2->next->prev = temp1;
				temp2->prev = temp1->prev;
				temp2->next = temp1;
				if (temp1->prev)
					temp1->prev->next = temp2;
				else
					*envp = temp2;
				temp1->prev = temp2;
				swapped = false;
			}
			else
				curr = curr->next;
		}
		if (swapped)
			break;
	}
}
