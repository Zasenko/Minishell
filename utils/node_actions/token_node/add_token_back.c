/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_token_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibondarc <ibondarc@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 17:55:21 by ibondarc          #+#    #+#             */
/*   Updated: 2025/02/12 17:55:21 by ibondarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

bool	add_token_back(t_token **token, t_token *new)
{
	t_token	*last;

	if (!new)
		return (false);
	if (*token == NULL)
	{
		*token = new;
		return (true);
	}
	last = last_token_node(*token);
	last->next = new;
	new->prev = last;
	return (true);
}
