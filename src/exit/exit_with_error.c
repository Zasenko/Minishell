/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_with_error.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibondarc <ibondarc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 12:06:08 by ibondarc          #+#    #+#             */
/*   Updated: 2025/02/05 12:06:08 by ibondarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	exit_with_error(t_app *shell, int status, char *message)
{
	if (message)
		print_message(message, false);
	free_envp_list(&shell->envp);
	free_list(shell);
	exit(status);
}

void	exit_child(t_app *shell, int status, char *message)
{
    if (message)
        print_message(message, false);
    free_envp_list(&shell->envp);
    free_list_in_child(shell);
    exit(status);
}
