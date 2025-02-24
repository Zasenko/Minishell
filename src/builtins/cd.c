/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzasenko <dzasenko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 09:57:45 by dzasenko          #+#    #+#             */
/*   Updated: 2025/02/24 13:11:32 by dzasenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int ft_cd(t_cmd *cmd, char **env)
{
    char buf[MAXPATHLEN];
    char *current_dir;
    int result;
    
    if (!cmd)
        return (EXIT_FAILURE);
    (void)env;

    current_dir = NULL;
    current_dir = getcwd(buf, MAXPATHLEN);
    if (!current_dir)
        return (perror("getcwd"), errno);
    if (cmd->args[1] != NULL)
    {
        result =chdir(cmd->args[1]);
        if (result == -1)
            return (perror("chdir"), errno);
    }
    return (SUCCESS);
}