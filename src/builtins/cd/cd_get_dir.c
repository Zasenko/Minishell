/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_get_dir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibondarc <ibondarc@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 13:34:48 by ibondarc          #+#    #+#             */
/*   Updated: 2025/05/09 13:36:29 by ibondarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	cd_get_dir(t_cmd *cmd, t_pwd *pwd, t_app *shell, bool is_child)
{
	if (arr2d_len(cmd->args) > 2)
		return (ft_putstr_fd(CD_TMA, 2), EXIT_FAILURE);
	if (cmd->args[1] == NULL || !ft_strcmp("~", cmd->args[1]))
	{
		if (!pwd->home || !pwd->home->envp)
			return (ft_putstr_fd(CD_HNS, 2), EXIT_FAILURE);
		pwd->dir = ft_strdup(pwd->home->envp);
	}
	else
	{
		if (!ft_strcmp("-", cmd->args[1]))
		{
			if (!pwd->oldpwd || !pwd->oldpwd->envp)
				return (ft_putstr_fd(CD_ONS, 2), EXIT_FAILURE);
			pwd->dir = ft_strdup(pwd->oldpwd->envp);
		}
		else
			pwd->dir = ft_strdup(cmd->args[1]);
	}
	if (!pwd->dir)
		exit_malloc(shell, is_child);
	return (SUCCESS);
}
