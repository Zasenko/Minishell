/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibondarc <ibondarc@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 13:44:19 by ibondarc          #+#    #+#             */
/*   Updated: 2025/02/10 13:44:19 by ibondarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	create__env_value(t_app *shell, char *buf)
{
	t_envp	*new;
	char	*name;
	char	*value;
	char	*full_value;

	name = ft_strdup("_");
	if (!name)
		return (false);
	value = ft_strdup(getcwd(buf, MAXPATHLEN));
	if (!value)
		return (free(name), false);
	full_value = ft_strjoin(value, "/./minishell");
	free(value);
	if (!full_value)
		return (free(name), false);
	new = create_new_envp(full_value, name);
	if (!new)
		return (free(name), free(full_value), false);
	add_envp_back(&shell->envp, new);
	return (true);
}

bool	make_new_envp(t_app *shell, char *str, char **name, char **env_var)
{
	char	*value;
	t_envp	*new;

	value = ft_strchr(str, '=', true);
	if (value)
	{
		*env_var = ft_strdup(value);
		if (!(*env_var))
			return (false);
	}
	new = create_new_envp(*env_var, *name);
	if (!new)
		return (free(*env_var), free(*name), false);
	add_envp_back(&shell->envp, new);
	return (true);
}

bool	create_env_copy(t_app *shell, char **envp, int *i)
{
	int		j;
	char	*name;
	char	*env_var;
	char	*s;

	env_var = NULL;
	while (envp[*i] != NULL)
	{
		j = 0;
		s = envp[*i];
		while (s[j] != '=')
			j++;
		name = ft_substr(s, 0, j);
		if (!name)
			return (free(env_var), false);
		if (!make_new_envp(shell, envp[*i], &name, &env_var))
			return (false);
		env_var = NULL;
		(*i)++;
	}
	return (true);
}

void	create_env_if_its_empty(t_app *shell, char *buf)
{
	if (!create_pwd_env_value(shell))
		exit_with_error(shell, 1, MALLOC_FAIL);
	if (!create_shell_lvl_env_value(shell))
		exit_with_error(shell, 1, MALLOC_FAIL);
	if (!create_oldpwd_env_value(shell))
		exit_with_error(shell, 1, MALLOC_FAIL);
	if (!create__env_value(shell, buf))
		exit_with_error(shell, 1, MALLOC_FAIL);
}

void	copy_env(t_app *shell, char **envp)
{
	int		i;
	char	buf[MAXPATHLEN];

	if (!shell)
		return ;
	if (envp && envp[0])
	{
		i = 0;
		if (!create_env_copy(shell, envp, &i))
			exit_with_error(shell, 1, MALLOC_FAIL);
		if (find_envp_node(shell->envp, "PWD") == NULL)
			if (!create_pwd_env_value(shell))
				exit_with_error(shell, 1, MALLOC_FAIL);
		if (find_envp_node(shell->envp, "SHLVL") == NULL)
			if (!create_shell_lvl_env_value(shell))
				exit_with_error(shell, 1, MALLOC_FAIL);
		if (find_envp_node(shell->envp, "OLDPWD") == NULL)
			if (!create_oldpwd_env_value(shell))
				exit_with_error(shell, 1, MALLOC_FAIL);
		if (find_envp_node(shell->envp, "_") == NULL)
			if (!create__env_value(shell, buf))
				exit_with_error(shell, 1, MALLOC_FAIL);
	}
	else
		create_env_if_its_empty(shell, buf);
}
