/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzasenko <dzasenko@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 16:15:41 by dzasenko          #+#    #+#             */
/*   Updated: 2025/02/12 16:26:44 by dzasenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	is_builtin_func(char *cmd)
{
	if (!cmd)
		return (false);
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

void	sorting_env(t_sort_env *sort_env, t_envp **envp)
{
	sort_env->temp1 = sort_env->curr;
	sort_env->temp2 = sort_env->curr->next;
	sort_env->temp1->next = sort_env->temp2->next;
	if (sort_env->temp2->next)
		sort_env->temp2->next->prev = sort_env->temp1;
	sort_env->temp2->prev = sort_env->temp1->prev;
	sort_env->temp2->next = sort_env->temp1;
	if (sort_env->temp1->prev)
		sort_env->temp1->prev->next = sort_env->temp2;
	else
		*envp = sort_env->temp2;
	sort_env->temp1->prev = sort_env->temp2;
	sort_env->swapped = false;
}

void	sort_environment(t_envp **envp)
{
	t_sort_env	sort_env;

	if (!envp || !(*envp))
		return ;
	while (1)
	{
		sort_env.swapped = true;
		sort_env.curr = *envp;
		while (sort_env.curr->next)
		{
			if (ft_strcmp(sort_env.curr->name, sort_env.curr->next->name) > 0)
			{
				sorting_env(&sort_env, envp);
			}
			else
				sort_env.curr = sort_env.curr->next;
		}
		if (sort_env.swapped)
			break ;
	}
}
