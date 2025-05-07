/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzasenko <dzasenko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 11:25:00 by dzasenko          #+#    #+#             */
/*   Updated: 2025/05/07 13:52:17 by dzasenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	cd_change_old_pwd(t_app *shell, t_pwd *pwd, bool is_child)
{
	char	*new_oldpwd;

	new_oldpwd = NULL;
	if (pwd->pwd && pwd->pwd->envp)
	{
		new_oldpwd = ft_strdup(pwd->pwd->envp);
		if (!new_oldpwd)
		{
			if (pwd->changed_dir)
				free(pwd->changed_dir);
			exit_malloc(shell, is_child);
		}
		if (pwd->oldpwd->envp)
		{
			free(pwd->oldpwd->envp);
			pwd->oldpwd->envp = NULL;
		}
		pwd->oldpwd->envp = new_oldpwd;
	}
}

void	handle_exit_and_free(t_app *shell, t_pwd *pwd, bool is_child)
{
	if (pwd->changed_dir)
		free(pwd->changed_dir);
	exit_malloc(shell, is_child);
}

void	cd_set_old_pwd(t_app *shell, t_pwd *pwd, bool is_child)
{
	char	*new_old_pwd;
	char	*new_old_pwd_name;

	new_old_pwd = ft_strdup(pwd->pwd->envp);
	if (!new_old_pwd)
		handle_exit_and_free(shell, pwd, is_child);
	new_old_pwd_name = ft_strdup("OLDPWD");
	if (!new_old_pwd_name)
	{
		free(new_old_pwd);
		handle_exit_and_free(shell, pwd, is_child);
	}
	if (!create_new_pwd_node(shell, new_old_pwd, new_old_pwd_name))
		handle_exit_and_free(shell, pwd, is_child);
}

void	cd_change_pwd(t_app *shell, t_pwd *pwd, bool is_child)
{
	char	*new_pwd;

	new_pwd = NULL;
	new_pwd = ft_strdup(pwd->changed_dir);
	if (!new_pwd)
	{
		if (pwd->changed_dir)
			free(pwd->changed_dir);
		exit_malloc(shell, is_child);
	}
	if (pwd->pwd->envp != NULL)
	{
		free(pwd->pwd->envp);
		pwd->pwd->envp = NULL;
	}
	pwd->pwd->envp = new_pwd;
}

int	cd_change_env(t_app *shell, t_pwd *pwd, bool is_child)
{
	if (pwd->oldpwd)
		cd_change_old_pwd(shell, pwd, is_child);
	else
		cd_set_old_pwd(shell, pwd, is_child);
	if (pwd->pwd)
		cd_change_pwd(shell, pwd, is_child);
	return (EXIT_SUCCESS);
}
