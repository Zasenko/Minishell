/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_len.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmitryzasenko <dmitryzasenko@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 16:48:41 by dmitryzasen       #+#    #+#             */
/*   Updated: 2025/02/11 16:49:25 by dmitryzasen      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	cmd_len(t_cmd *cmd)
{
	t_cmd	*temp;
	int		i;

	i = 0;
	temp = cmd;
	if (!temp)
		return (i);
	while (temp != NULL)
	{
		i++;
		temp = temp->next;
	}
	return (i);
}
