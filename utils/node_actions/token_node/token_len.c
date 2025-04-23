/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_len.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibondarc <ibondarc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 17:54:55 by ibondarc          #+#    #+#             */
/*   Updated: 2025/02/12 17:54:55 by ibondarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	token_len(t_token *token)
{
	t_token	*temp;
	int		i;

	i = 0;
	temp = token;
	if (!temp)
		return (i);
	while (temp != NULL)
	{
		i++;
		temp = temp->next;
	}
	return (i);
}
