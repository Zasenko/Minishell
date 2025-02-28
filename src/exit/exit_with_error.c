/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_with_error.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 12:06:08 by marvin            #+#    #+#             */
/*   Updated: 2025/02/05 12:06:08 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"



void 	exit_with_error(t_app *shell, int status, char *message)
{
    if (message)
        print_message(message, false);
    // free_envp_list(&shell->envp);
    free_list(shell);
    exit(status);
}