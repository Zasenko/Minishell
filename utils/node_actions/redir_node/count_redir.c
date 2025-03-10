/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 15:10:25 by marvin            #+#    #+#             */
/*   Updated: 2025/02/14 15:10:25 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	count_redir(t_redir *redir)
{
	t_redir	*temp;
	int		i;

	i = 0;
	temp = redir;
	if (!temp)
		return (i);
	while (temp && temp->type != PIPE)
	{
		if (temp->type == REDIR_IN || temp->type == REDIR_OUT)
        	i++;
		temp = temp->next;
	}
	return (i);
}