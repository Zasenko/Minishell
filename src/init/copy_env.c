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

bool	create_pwd_env_value(t_app *shell)
{
	char	buf[MAXPATHLEN];
	char	*name;
	char	*value;

	name = ft_strdup("PWD");
	if (!name)
		return (false);
	value = ft_strdup(getcwd(buf, MAXPATHLEN));
	if (!value)
	{
		free(name);
		return (false);
	}
	add_envp_back(&shell->envp, create_new_envp(value, name));
	return (true);
}

bool	create_shell_lvl_env_value(t_app *shell)
{
	char	*name;
	char	*value;

	name = ft_strdup("1");
	if (!name)
		return (false);
	value = ft_strdup("SHLVL");
	if (!value)
	{
		free(name);
		return (false);
	}
	add_envp_back(&shell->envp, create_new_envp(value, name));
	return (true);
}

bool	create_env_copy(t_app *shell, char **envp, int *i)
{
	int		j;
	char	*name;
	char	*env_var;
	char	*s;

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
		add_envp_back(&shell->envp, create_new_envp(env_var, name));
		(*i)++;
	}
	return (true);
}

void	copy_env(t_app *shell, char **envp)
{
	int	i;

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
		if (!create_pwd_env_value(shell) && !create_shell_lvl_env_value(shell))
			exit_with_error(shell, 1, MALLOC_FAIL);
	}
}
