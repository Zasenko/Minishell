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

int	get_envp_len(t_envp *envp)
{
	t_envp	*temp;
	int		i;

	i = 0;
	temp = envp;
	if (!temp)
		return (i);
	while (temp != NULL)
	{
		i++;
		temp = temp->next;
	}
	return (i);
}
