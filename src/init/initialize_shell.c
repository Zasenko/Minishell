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

t_cmd *initialize_cmd(void)
{
    t_cmd *new;

    new = malloc(sizeof(t_cmd));
    if (!new)
        exit(1);
    new->args = NULL;
	new->input = NULL;
	new->output = NULL;
	new->next = NULL;
    new->prev = NULL;
	new->append = 0;
    return new;
}

void  initialize_shell(t_app *shell)
{
    shell->path = NULL;
    shell->user = NULL;
    shell->name = NULL;
    shell->pwd = NULL;
    shell->prompt = NULL;
    shell->cmd = NULL;
}
