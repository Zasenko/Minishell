/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzasenko <dzasenko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 09:57:45 by dzasenko          #+#    #+#             */
/*   Updated: 2025/02/21 13:38:58 by dzasenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int ft_cd(t_cmd *cmd, char **env)
{
    char buf[MAXPATHLEN];
    char *current_dir;
    int result;
    
    if (!cmd)
        return ( 0);
    (void)env;

    current_dir = NULL;
    current_dir = getcwd(buf, MAXPATHLEN);
    if (!current_dir)
        return (perror("getcwd"), 0);
    if (cmd->args[1] != NULL)
    {
        result = chdir(cmd->args[1]);
        if (!result)
            return (0);
        else if (result == -1)
            return perror("chdir"), 0;
    }
    return 1;
}

