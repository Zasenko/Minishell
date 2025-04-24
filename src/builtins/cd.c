/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibondarc <ibondarc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 09:57:45 by dzasenko          #+#    #+#             */
/*   Updated: 2025/03/24 13:33:47 by ibondarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	cd_get_dir(t_cmd *cmd, t_pwd *pwd)
{
	if (arr2d_len(cmd->args) > 2)
		return (ft_putstr_fd("cd: too many arguments\n", 2), EXIT_FAILURE);
	if (cmd->args[1] == NULL || !ft_strcmp("~", cmd->args[1]))
	{
		if (!pwd->home || !pwd->home->envp)
			return (ft_putstr_fd("cd: HOME not set\n", 2), EXIT_FAILURE);
		pwd->dir = ft_strdup(pwd->home->envp);
	}
	else
	{
		if (!ft_strcmp("-", cmd->args[1]))
		{
			if (!pwd->oldpwd || !pwd->oldpwd->envp)
			{
				ft_putstr_fd("minishell: cd: OLDPWD not set\n", 2);
				return (EXIT_FAILURE);
			}
			pwd->dir = ft_strdup(pwd->oldpwd->envp);
		}
		else
			pwd->dir = ft_strdup(cmd->args[1]);
	}
	return (SUCCESS);
}


int	cd_change_dir(char *dir, char **changed_dir)
{
	char	buf[MAXPATHLEN];
	int		result;

	result = chdir(dir);
	if (result == -1)
	{
		ft_putstr_fd("minishell: cd: ", 2);
		ft_putstr_fd(dir, 2);
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(strerror(errno), 2);
		ft_putstr_fd("\n", 2);
		return (EXIT_FAILURE);
	}
	changed_dir[0] = getcwd(buf, MAXPATHLEN);
	return (SUCCESS);
}

int	ft_cd(t_cmd *cmd, t_app *shell, bool is_child)
{
	t_pwd	pwd;

	pwd.home = find_envp_node(shell->envp, "HOME");
	pwd.oldpwd = find_envp_node(shell->envp, "OLDPWD");
	pwd.pwd = find_envp_node(shell->envp, "PWD");
	pwd.dir = NULL;
	pwd.changed_dir = NULL;

	if (cd_get_dir(cmd, &pwd) == EXIT_FAILURE)
		return (EXIT_FAILURE);

	char	buf[MAXPATHLEN];
	int	result;
	result = chdir(pwd.dir);
	if (result == -1)
	{
		ft_putstr_fd("minishell: cd: ", 2);
		ft_putstr_fd(pwd.dir, 2);
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(strerror(errno), 2);
		ft_putstr_fd("\n", 2);
		if (pwd.dir)
			free(pwd.dir);
		return (EXIT_FAILURE);
	}
	if (pwd.dir)
		free(pwd.dir);
	pwd.changed_dir = getcwd(buf, MAXPATHLEN);
	if (!pwd.changed_dir)
		return (perror("getcwd"), errno);
	if (cmd->args[1] != NULL && !ft_strcmp("-", cmd->args[1]))
	{
		ft_putstr_fd(pwd.changed_dir, 1);
		ft_putstr_fd("\n", 1);
	}
	if (!is_child)
		cd_change_env(shell, &pwd, is_child);
	return (SUCCESS);
}
