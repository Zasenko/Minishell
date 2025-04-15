/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibondarc <ibondarc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 13:44:19 by ibondarc          #+#    #+#             */
/*   Updated: 2025/02/10 13:44:19 by ibondarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	reduce_shell_level(char *name, char *env_var)
{
	int level;

	if (!name)
		return (false);
	if (!ft_strcmp(name, "SHLVL"))
	{
		level = ft_atoi(env_var);
		level++;
		free(env_var);
		env_var = ft_itoa(level);
		if (!env_var)
			return (false);
	}
	return (true);
}

bool	create_env_copy(t_app *shell, char **envp, int *i)
{
	int j;
	char *name;
	char *env_var;
	char *s;

	while (envp[*i] != NULL)
	{
		j = 0;
		s = envp[*i];
		while (s[j] != '=')
			j++;
		env_var = ft_strdup(ft_strchr(envp[*i], '=', true));
		if (!env_var)
			return (false);
		name = ft_substr(s, 0, j);
		if (!name)
			return (false);
		if (!reduce_shell_level(name, env_var))
			return (false);
		add_envp_back(&shell->envp, create_new_envp(env_var, name));
		(*i)++;
	}
	return (true);
}

void	copy_env(t_app *shell, char **envp)
{
	int i;
	char buf[MAXPATHLEN];
	char *dir;

	if (!shell)
		return ;
	if (envp && envp[0])
	{
		i = 0;
		if (!create_env_copy(shell, envp, &i))
			exit_with_error(shell, 1, MALLOC_FAIL);
	}
	else
	{
		dir = NULL;
		dir = getcwd(buf, MAXPATHLEN);
		add_envp_back(&shell->envp, create_new_envp(dir, "PWD"));
		add_envp_back(&shell->envp, create_new_envp("1", "SHLVL"));
	}
}
