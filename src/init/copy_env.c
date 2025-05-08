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
	t_envp	*new;
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
	new = create_new_envp(value, name);
	if (!new)
		return (free(name), free(value), false);
	add_envp_back(&shell->envp, new);
	return (true);
}

bool	create_shell_lvl_env_value(t_app *shell)
{
	t_envp	*new;
	char	*name;
	char	*value;

	name = ft_strdup("SHLVL");
	if (!name)
		return (false);
	value = ft_strdup("1");
	if (!value)
		return (free(name), false);
	new = create_new_envp(value, name);
	if (!new)
		return (free(name), free(value), false);
	add_envp_back(&shell->envp, new);
	return (true);
}

bool	create_oldpwd_env_value(t_app *shell)
{
	t_envp	*new;
	char	*name;

	name = ft_strdup("OLDPWD");
	if (!name)
		return (false);
	new = create_new_envp(NULL, name);
	if (!new)
		return (free(name), false);
	add_envp_back(&shell->envp, new);
	return (true);
}

bool	create__env_value(t_app *shell)
{
	t_envp	*new;
	char	buf[MAXPATHLEN];
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

bool	create_env_copy(t_app *shell, char **envp, int *i)
{
	int		j;
	char	*name;
	char	*env_var;
	char	*s;
	t_envp	*new;

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
			return (free(env_var), false);

		new = create_new_envp(env_var, name);
		if (!new)
			return (free(env_var), free(name), false);
		add_envp_back(&shell->envp, new);
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
			if (!create__env_value(shell))
				exit_with_error(shell, 1, MALLOC_FAIL);
	}
	else
	{
		if (!create_pwd_env_value(shell))
			exit_with_error(shell, 1, MALLOC_FAIL);
		if (!create_shell_lvl_env_value(shell))
			exit_with_error(shell, 1, MALLOC_FAIL);
		if (!create_oldpwd_env_value(shell))
			exit_with_error(shell, 1, MALLOC_FAIL);
		if (!create__env_value(shell))
			exit_with_error(shell, 1, MALLOC_FAIL);
	}
}
