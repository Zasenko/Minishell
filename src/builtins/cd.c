/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzasenko <dzasenko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 09:57:45 by dzasenko          #+#    #+#             */
/*   Updated: 2025/02/20 15:23:20 by dzasenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int ft_cd(t_cmd *cmd, char **env)
{
    if (!cmd)
        return ( 0);
    (void)env;
    char buf[MAXPATHLEN];
    char *current_dir;

    current_dir = NULL;
    current_dir = getcwd(buf, MAXPATHLEN);
    if (!current_dir)
        return (perror("getcwd"), 0);
    if (cmd->args[1] != NULL)
    {
        int result;
        result = chdir(cmd->args[1]);
        if (!result)
        {
            ft_pwd();
            return (1);
        }
        else if (result == -1)
            return perror("chdir"), 0;
    }
    return 1;
}

