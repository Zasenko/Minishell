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
		char *new_pwd = ft_strdup(dir);
		if (!new_pwd)
		{
			exit_with_error(shell, 1, MALLOC_FAIL);
		}
		char *new_pwd_name= ft_strdup("PWD");
		if (!new_pwd)
		{
			free(new_pwd);
			exit_with_error(shell, 1, MALLOC_FAIL);
		}
		add_envp_back(&shell->envp, create_new_envp(new_pwd, new_pwd_name));

		char *new_SHLVL = ft_strdup("1");
		if (!new_SHLVL)
		{
			exit_with_error(shell, 1, MALLOC_FAIL);
		}
		char *new_SHLVL_name= ft_strdup("SHLVL");
		if (!new_SHLVL_name)
		{
			free(new_SHLVL);
			exit_with_error(shell, 1, MALLOC_FAIL);
		}
		add_envp_back(&shell->envp, create_new_envp(new_SHLVL, new_SHLVL_name));
	}
}
