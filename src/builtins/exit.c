/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzasenko <dzasenko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 09:59:49 by dzasenko          #+#    #+#             */
/*   Updated: 2025/02/24 11:03:46 by dzasenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int ft_exit(t_cmd *cmd, t_app *shell, int is_parent)
{
    int exit_code;

    exit_code = 0;
    
    if (cmd->args[1] != NULL)
    {
        // todo check numbers and +- only
        exit_code = ft_atoi(cmd->args[1]);
    }

    if (is_parent)
    {
        free_list(shell);
        printf("exit\n");
        exit(exit_code);
    }
    else
        exit(exit_code);
}