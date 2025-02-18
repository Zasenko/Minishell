/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_shell.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 21:24:36 by marvin            #+#    #+#             */
/*   Updated: 2025/02/03 21:24:36 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void  initialize_shell(t_app *shell, char **envp)
{
    shell->path = NULL;
    shell->env_var = NULL;
    shell->user = NULL;
    shell->name = NULL;
    shell->pwd = NULL;
    shell->prompt = NULL;
    shell->envp = NULL;
    shell->cmd = NULL;
    shell->tokens = NULL;
    shell->env = envp;
    copy_env(shell, envp);
}
