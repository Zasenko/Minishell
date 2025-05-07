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

bool	create_new_pwd_node(t_app *shell, char *old_pwd, char *new_pwd)
{
	t_envp	*node;

	node = create_new_envp(old_pwd, new_pwd);
	if (!node)
	{
		free(old_pwd);
		free(new_pwd);
		return (false);
	}
	add_envp_back(&shell->envp, node);
	return (true);
}

int	cd_change_dir(t_pwd *pwd)
{
	int	result;

	result = chdir(pwd->dir);
	if (result == -1)
	{
		ft_putstr_fd("minishell: cd: ", 2);
		ft_putstr_fd(pwd->dir, 2);
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(strerror(errno), 2);
		ft_putstr_fd("\n", 2);
		if (pwd->dir)
		{
			free(pwd->dir);
			pwd->dir = NULL;
		}
		return (EXIT_FAILURE);
	}
	if (pwd->dir)
	{
		free(pwd->dir);
		pwd->dir = NULL;
	}
	return (SUCCESS);
}

void	create_cd_pwd(t_pwd *pwd, t_envp *envp)
{
	pwd->home = find_envp_node(envp, "HOME");
	pwd->oldpwd = find_envp_node(envp, "OLDPWD");
	pwd->pwd = find_envp_node(envp, "PWD");
	pwd->dir = NULL;
	pwd->changed_dir = NULL;
}

int	ft_cd(t_cmd *cmd, t_app *shell, bool is_child)
{
	int		result;
	t_pwd	pwd;
	char	buf[MAXPATHLEN];

	create_cd_pwd(&pwd, shell->envp);
	if (cd_get_dir(cmd, &pwd, shell, is_child) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	result = cd_change_dir(&pwd);
	if (result == EXIT_FAILURE)
		return (EXIT_FAILURE);
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
