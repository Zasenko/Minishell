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

int ft_cd(t_cmd *cmd, t_app *shell, bool is_child)
{
    t_envp *home_node = find_envp_node(shell->envp, "HOME");
    t_envp *oldpwd_node = find_envp_node(shell->envp, "OLDPWD");
    t_envp *pwd_node = find_envp_node(shell->envp, "PWD");
    char *dir = NULL;
    int result;

    if (arr2d_len(cmd->args) > 2)
    {
        ft_putstr_fd("cd: too many arguments\n", 2);
        return (EXIT_FAILURE);
    }
    
    if (cmd->args[1] == NULL)
    {
        if (!home_node || !home_node->envp)
        {
            ft_putstr_fd("cd: HOME not set\n", 2);
            return (EXIT_FAILURE);
        }
        dir = home_node->envp;
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
            dir = oldpwd_node->envp;
            //ft_pwd();
        }
        else
        {
            dir = cmd->args[1];
        }
    }

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
    
    char buf[MAXPATHLEN];
    char *current_dir;
    current_dir = NULL;
    current_dir = getcwd(buf, MAXPATHLEN);

    if (!current_dir)
        return (perror("getcwd"), errno);
    
    if (cmd->args[1] != NULL && !ft_strcmp("-", cmd->args[1]))
    {
        ft_putstr_fd(current_dir, 1);
        ft_putstr_fd("\n", 1);
    }

    if (!is_child)
    {
        if (oldpwd_node)
        {
            char *new_oldpwd = NULL;
            if (pwd_node && pwd_node->envp)
            {
                new_oldpwd = ft_strdup(pwd_node->envp);
                if (!new_oldpwd)
                {
                    return EXIT_FAILURE;
                }
                if (oldpwd_node->envp)
                {
                    free(oldpwd_node->envp);
                    oldpwd_node->envp = NULL;
                }
                oldpwd_node->envp = new_oldpwd;
            }
        }
        else
        {
            char *new_old_pwd = ft_strdup(pwd_node->envp);
		    if (!new_old_pwd)
		    {
		    	exit_with_error(shell, 1, MALLOC_FAIL);
		    }
		    char *new_old_pwd_name= ft_strdup("OLDPWD");
		    if (!new_old_pwd_name)
		    {
		    	free(new_old_pwd);
		    	exit_with_error(shell, 1, MALLOC_FAIL);
		    }
		    add_envp_back(&shell->envp, create_new_envp(new_old_pwd, new_old_pwd_name));
        }
        if (pwd_node)
        {
            char *new_pwd = ft_strdup(current_dir);
            if (!new_pwd)
            {
                return EXIT_FAILURE;
            }
            if (pwd_node->envp != NULL)
            {
                free(pwd_node->envp);
                pwd_node->envp = NULL;

            }
            pwd_node->envp = new_pwd;

        }
    }

    return (SUCCESS);
}
