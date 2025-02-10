/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_node_back.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 12:24:27 by marvin            #+#    #+#             */
/*   Updated: 2025/02/06 12:24:27 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	add_cmd_back(t_cmd **cmd, t_cmd *new)
{
	t_cmd	*last;

	if (!new)
		return ;
	if (*cmd == NULL)
	{
		*cmd = new;
		return ;
	}
	last = last_cmd_node(*cmd);
	last->next = new;
	new->prev = last;
}