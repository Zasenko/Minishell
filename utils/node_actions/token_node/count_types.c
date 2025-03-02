/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_types.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 15:10:25 by marvin            #+#    #+#             */
/*   Updated: 2025/02/14 15:10:25 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	count_types(t_token *token, t_type type)
{
	t_token	*temp;
	int		i;

	i = 0;
	temp = token;
	if (!temp)
		return (i);
	while (temp && temp->type == type && temp->type != PIPE)
	{
        i++;
		temp = temp->next;
	}
	return (i);
}