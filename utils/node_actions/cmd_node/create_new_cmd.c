/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibondarc <ibondarc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 19:36:07 by ibondarc          #+#    #+#             */
/*   Updated: 2025/02/05 19:36:07 by ibondarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_cmd	*create_new_cmd(void)
{
	t_cmd	*new;

	new = malloc(sizeof(t_cmd));
	if (!new)
		return (NULL);
	new->cmd = NULL;
	new->args = NULL;
	new->pipe_fd[0] = -1;
	new->pipe_fd[1] = -1;
	new->is_build = false;
	new->redirs = NULL;
	new->prev = NULL;
	new->next = NULL;
	new->pid = -1;
	return (new);
}
