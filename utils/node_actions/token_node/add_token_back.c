/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_token_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 17:55:21 by marvin            #+#    #+#             */
/*   Updated: 2025/02/12 17:55:21 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	add_token_back(t_token **token, t_token *new)
{
	t_token	*last;

	if (!new)
		return ;
	if (*token == NULL)
	{
		*token = new;
		return ;
	}
	last = last_token_node(*token);
	last->next = new;
	new->prev = last;
}