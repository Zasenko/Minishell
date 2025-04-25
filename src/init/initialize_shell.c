/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_shell.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibondarc <ibondarc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 21:24:36 by ibondarc          #+#    #+#             */
/*   Updated: 2025/02/03 21:24:36 by ibondarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	initialize_shell(t_app *shell, char **envp)
{
	shell->env_var = NULL;
	shell->user = NULL;
	shell->name = NULL;
	shell->pwd = NULL;
	shell->prompt = NULL;
	shell->envp = NULL;
	shell->prev_pipe = -1;
	shell->last_exit_code = 0;
	shell->is_envp_list_changed = false;
	shell->cmd = NULL;
	shell->tokens = NULL;
	shell->heredock_num = 1;
	shell->is_valid_syntax = true;
	copy_env(shell, envp);
}
