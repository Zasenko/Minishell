/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   last_token_node.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 17:55:02 by marvin            #+#    #+#             */
/*   Updated: 2025/02/12 17:55:02 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_token *last_token_node(t_token *node)
{
	if (node == NULL)
		return (NULL);
	while (node->next != NULL)
		node = node->next;
	return (node);
}