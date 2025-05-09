/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibondarc <ibondarc@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 12:20:16 by ibondarc          #+#    #+#             */
/*   Updated: 2025/05/09 12:26:16 by ibondarc         ###   ########.fr       */
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
