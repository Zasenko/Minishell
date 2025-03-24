/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzasenko <dzasenko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 09:57:45 by dzasenko          #+#    #+#             */
/*   Updated: 2025/03/24 11:53:07 by dzasenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int ft_cd(t_cmd *cmd, t_app *shell, bool is_child)
{
    char buf[MAXPATHLEN];
    char *current_dir;
    int result;
    
    if (!cmd)
        return (EXIT_FAILURE);

    current_dir = NULL;
    current_dir = getcwd(buf, MAXPATHLEN);
    if (!current_dir)
        return (perror("getcwd"), errno);
    
    if (arr2d_len(cmd->args) > 2)
    {
        ft_putstr_fd("cd: too many arguments\n", 2);
        return (EXIT_FAILURE);
    }
    
    if (cmd->args[1] != NULL)
    {
        if (!ft_strncmp("-", cmd->args[1], ft_strlen(cmd->args[1])))   
        {
            t_envp *oldpwd_node = find_envp_node(shell->envp, "OLDPWD");
            t_envp *pwd_node = find_envp_node(shell->envp, "PWD");
            
            if (!oldpwd_node || !oldpwd_node->envp)
            {
                ft_putstr_fd("cd: OLDPWD not set\n", 2);
                return (EXIT_FAILURE);
            }
            result = chdir(oldpwd_node->envp);
            if (result == -1)
            {
                perror(oldpwd_node->envp);
                // ft_putstr_fd("cd: ", 2);
                // ft_putstr_fd(oldpwd_node->envp, 2);
                // ft_putstr_fd(": No such file or directory\n", 2);
                return (EXIT_FAILURE);
            }
            if (!is_child)
            {
                char *temp = pwd_node->envp;
                if (pwd_node)
                {
                    char *new_pwd = ft_strdup(oldpwd_node->envp);
                    if (!new_pwd)
                    {
                        return EXIT_FAILURE;
                    }
                    if (pwd_node->envp)
                    {
                        free (pwd_node->envp);
                    }
                    pwd_node->envp = new_pwd;
                }
                if (oldpwd_node->envp)
                {
                    free(oldpwd_node->envp);
                }
                oldpwd_node->envp = temp;
            }
        }
        else {
            result = chdir(cmd->args[1]);
            if (result == -1)
            {
                ft_putstr_fd("cd: ", 2);
                ft_putstr_fd(cmd->args[1], 2);
                ft_putstr_fd(": No such file or directory\n", 2);
                return (EXIT_FAILURE);
            }
        }
    }
    else
    {
        t_envp *home_node = find_envp_node(shell->envp, "HOME");
        t_envp *oldpwd_node = find_envp_node(shell->envp, "OLDPWD");
        t_envp *pwd_node = find_envp_node(shell->envp, "PWD");
        if (!home_node || !home_node->envp)
        {
            ft_putstr_fd("cd: HOME not set\n", 2);
            return (EXIT_FAILURE);
        }
        result = chdir(home_node->envp);
        if (result == -1)
        {
            return (perror("chdir"), errno);
        }     
        if (!is_child)
        {
            if (oldpwd_node)
            {
                char *new_oldpwd = NULL;
                if (pwd_node->envp)
                {
                    new_oldpwd = ft_strdup(pwd_node->envp);
                    if (!new_oldpwd)
                    {
                        return EXIT_FAILURE;
                    }
                }
               
                if (oldpwd_node->envp)
                {
                    free (oldpwd_node->envp);
                }
                oldpwd_node->envp = new_oldpwd;
            }
        
            if (pwd_node)
            {
                char *new_pwd = ft_strdup(home_node->envp);
                if (!new_pwd)
                {
                    return EXIT_FAILURE;
                }
                if (pwd_node->envp)
                {
                    free (pwd_node->envp);
                }
                pwd_node->envp = new_pwd;
            }
        }
    }
    return (SUCCESS);
}

// int ft_cd(t_cmd *cmd, t_app *shell, bool is_child)
// {
//     char buf[MAXPATHLEN];
//     char *current_dir;
//     int result;
    
//     if (!cmd)
//         return (EXIT_FAILURE);

//     current_dir = NULL;
//     current_dir = getcwd(buf, MAXPATHLEN);
//     if (!current_dir)
//         return (perror("getcwd"), errno);
//     if (cmd->args[1] != NULL)
//     {
//         result =chdir(cmd->args[1]);
//         if (result == -1)
//             return (perror("chdir"), errno);
//     }
//     return (SUCCESS);
// }