/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_redir_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 17:55:21 by marvin            #+#    #+#             */
/*   Updated: 2025/02/12 17:55:21 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	add_redir_back(t_redir **redir, t_redir *new)
{
	t_redir	*last;

	if (!new)
		return ;
	if (*redir == NULL)
	{
		*redir = new;
		return ;
	}
	last = last_redir_node(*redir);
	last->next = new;
}