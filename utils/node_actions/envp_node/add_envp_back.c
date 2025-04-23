/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_node_back.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibondarc <ibondarc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 12:24:27 by ibondarc          #+#    #+#             */
/*   Updated: 2025/02/06 12:24:27 by ibondarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	add_envp_back(t_envp **envp, t_envp *new)
{
	t_envp	*last;

	if (!new)
		return ;
	if (*envp == NULL)
	{
		*envp = new;
		return ;
	}
	last = last_envp_node(*envp);
	last->next = new;
	new->prev = last;
}
