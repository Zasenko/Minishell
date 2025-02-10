/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 19:36:07 by marvin            #+#    #+#             */
/*   Updated: 2025/02/05 19:36:07 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_cmd *create_new_cmd(char **args)
{
	t_cmd *new;
	
	new = malloc(sizeof(t_cmd));
	if (!new)
		return NULL;
	new->args = args;
	new->fd_in = -1;
    new->fd_out = -1;
	new->append = false;
	new->prev = NULL;
	new->next = NULL;
	return new;
}