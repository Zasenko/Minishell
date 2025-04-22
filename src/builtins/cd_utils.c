/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzasenko <dzasenko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 11:25:00 by dzasenko          #+#    #+#             */
/*   Updated: 2025/04/22 11:53:34 by dzasenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	cd_change_old_pwd(t_app *shell, t_pwd *pwd, char *dir, char *current)
{
	char	*new_oldpwd;

	new_oldpwd = NULL;
	if (pwd->pwd && pwd->pwd->envp)
	{
		new_oldpwd = ft_strdup(pwd->pwd->envp);
		if (!new_oldpwd)
		{
			if (dir)
				free(dir);
			if (current)
				free(current);
			exit_with_error(shell, 1, "malloc error");
		}
		if (pwd->oldpwd->envp)
		{
			free(pwd->oldpwd->envp);
			pwd->oldpwd->envp = NULL;
		}
		pwd->oldpwd->envp = new_oldpwd;
	}
}

void	cd_set_old_pwd(t_app *shell, t_pwd *pwd, char *dir, char *current_dir)
{
	char	*new_old_pwd;
	char	*new_old_pwd_name;
	t_envp	*node;
	
	new_old_pwd = ft_strdup(pwd->pwd->envp);
	if (!new_old_pwd)
		exit_with_error(shell, 1, MALLOC_FAIL);
	new_old_pwd_name= ft_strdup("OLDPWD");
	if (!new_old_pwd_name)
	{
		free(new_old_pwd);
		exit_with_error(shell, 1, MALLOC_FAIL);
	}
	node = create_new_envp(new_old_pwd, new_old_pwd_name);
	if (!node)
	{
		free(new_old_pwd);
		free(new_old_pwd_name);
		if (dir)
			free(dir);
		if (current_dir)
			free(current_dir);
		exit_with_error(shell, 1, MALLOC_FAIL);
	}
	add_envp_back(&shell->envp, node);
}

void	cd_change_pwd(t_app *shell, t_pwd *pwd, char *dir, char *current_dir)
{
	char	*new_pwd;

	new_pwd = ft_strdup(current_dir);
	if (!new_pwd)
	{
		if (dir)
			free(dir);
		if (current_dir)
			free(current_dir);
		exit_with_error(shell, 1, MALLOC_FAIL);
	}
	if (pwd->pwd->envp != NULL)
	{
		free(pwd->pwd->envp);
		pwd->pwd->envp = NULL;
	}
	pwd->pwd->envp = new_pwd;
}

int	cd_change_env(t_app *shell, t_pwd *pwd, char *current_dir, char *dir)
{
	if (pwd->oldpwd)
		cd_change_old_pwd(shell, pwd, dir, current_dir);
	else
		cd_set_old_pwd(shell, pwd, dir, current_dir);
	if (pwd->pwd)
		cd_change_pwd(shell, pwd, dir, current_dir);
	return (EXIT_SUCCESS);
}
