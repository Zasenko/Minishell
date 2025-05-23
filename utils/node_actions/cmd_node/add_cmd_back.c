/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_node_back.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibondarc <ibondarc@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 12:24:27 by ibondarc          #+#    #+#             */
/*   Updated: 2025/02/06 12:24:27 by ibondarc         ###   ########.fr       */
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
