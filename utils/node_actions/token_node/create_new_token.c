/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_new_token.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 17:55:11 by marvin            #+#    #+#             */
/*   Updated: 2025/02/12 17:55:11 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_token *create_new_token(void)
{
	t_token *new;
	
	new = malloc(sizeof(t_token));
	if (!new)
		return NULL;
	new->value = NULL;
	new->type = -1;
	new->prev = NULL;
	new->next = NULL;
	return new;
}