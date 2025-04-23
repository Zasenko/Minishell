/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env_info.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibondarc <ibondarc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 13:26:13 by ibondarc          #+#    #+#             */
/*   Updated: 2025/02/05 13:26:13 by ibondarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	make_dafault_prompt(t_app *shell)
{
	char	buf[MAXPATHLEN];

	if (!shell->name)
	{
		shell->name = ft_strdup("shell-root");
		if (!shell->name)
			return (false);
	}
	if (!shell->user)
	{
		shell->user = ft_strdup("unknown-user");
		if (!shell->user)
			return (false);
	}
	shell->pwd = ft_strdup(getcwd(buf, MAXPATHLEN));
	if (!shell->pwd)
	{
		shell->pwd = ft_strdup("");
		if (!shell->pwd)
			return (false);
	}
	return (true);
}

bool	get_env_info(t_app *shell)
{
	t_envp	*envp;

	if (!shell || !shell->envp)
		return (false);
	envp = shell->envp;
	while (envp != NULL)
	{
		if (ft_strcmp(envp->name, "USER") == 0)
		{
			shell->user = ft_strdup(envp->envp);
			if (!shell->user)
				return (false);
		}
		else if (ft_strcmp(envp->name, "NAME") == 0)
		{
			shell->name = ft_strdup(envp->envp);
			if (!shell->name)
				return (false);
		}
		envp = envp->next;
	}
	if (!make_dafault_prompt(shell))
		return (false);
	return (true);
}
