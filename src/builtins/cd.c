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

int	cd_get_dir(t_cmd *cmd, t_envp *home_node, t_envp *oldpwd_node, char **dir)
{
	if (arr2d_len(cmd->args) > 2)
		return (ft_putstr_fd("cd: too many arguments\n", 2), EXIT_FAILURE);
	if (cmd->args[1] == NULL || !ft_strcmp("~", cmd->args[1]))
	{
		if (!home_node || !home_node->envp)
			return (ft_putstr_fd("cd: HOME not set\n", 2), EXIT_FAILURE);
		dir[0] = ft_strdup(home_node->envp);
	}
	else
	{
		if (!ft_strcmp("-", cmd->args[1]))
		{
			if (!oldpwd_node || !oldpwd_node->envp)
			{
				ft_putstr_fd("minishell: cd: OLDPWD not set\n", 2);
				return (EXIT_FAILURE);
			}
			dir[0] = ft_strdup(oldpwd_node->envp);
		}
		else
			dir[0] = ft_strdup(cmd->args[1]);
	}
	return (SUCCESS);
}


int	cd_change_dir(char *dir, char **changed_dir)
{
	char	buf[MAXPATHLEN];
	int	result;

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
	char	*dir;
	char	*changed_dir;
	t_pwd	pwd;

	pwd.home = find_envp_node(shell->envp, "HOME");
	pwd.oldpwd = find_envp_node(shell->envp, "OLDPWD");
	pwd.pwd = find_envp_node(shell->envp, "PWD");

	dir = NULL;
	changed_dir = NULL;

	if (cd_get_dir(cmd, pwd.home, pwd.oldpwd, &dir) == EXIT_FAILURE)
		return (EXIT_FAILURE);

	char	buf[MAXPATHLEN];
	int	result;

	result = chdir(dir);
	if (result == -1)
	{
		if (dir)
			free(dir);
		ft_putstr_fd("minishell: cd: ", 2);
		ft_putstr_fd(dir, 2);
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(strerror(errno), 2);
		ft_putstr_fd("\n", 2);
		return (EXIT_FAILURE);
	}
	if (dir)
		free(dir);
	changed_dir = getcwd(buf, MAXPATHLEN);
	if (!changed_dir)
		return (perror("getcwd"), errno);

	if (cmd->args[1] != NULL && !ft_strcmp("-", cmd->args[1]))
	{
		ft_putstr_fd(changed_dir, 1);
		ft_putstr_fd("\n", 1);
	}
	
	if (!is_child)
		cd_change_env(shell, &pwd, changed_dir, is_child);

	return (SUCCESS);
}
