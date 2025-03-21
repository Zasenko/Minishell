/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_new_redir.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 17:55:11 by marvin            #+#    #+#             */
/*   Updated: 2025/02/12 17:55:11 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_redir *create_new_redir(void)
{
	t_redir *new;
	
	new = malloc(sizeof(t_redir));
	if (!new)
		return NULL;
	new->value = NULL;
	new->type = -1;
	new->fd = -1;
	new->stop_word = NULL;
	new->next = NULL;
	new->heredock_with_quotes = false;
	return new;
}