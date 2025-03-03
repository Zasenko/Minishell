/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_len.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 17:54:55 by marvin            #+#    #+#             */
/*   Updated: 2025/02/12 17:54:55 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	redir_len(t_redir *redir)
{
	t_redir	*temp;
	int		i;

	i = 0;
	temp = redir;
	if (!temp)
		return (i);
	while (temp != NULL)
	{
		i++;
		temp = temp->next;
	}
	return (i);
}
