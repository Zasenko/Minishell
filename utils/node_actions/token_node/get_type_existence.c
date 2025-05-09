/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_token_type.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibondarc <ibondarc@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 16:50:34 by ibondarc          #+#    #+#             */
/*   Updated: 2025/02/17 16:50:34 by ibondarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

bool	get_type_existence(t_token *token, t_type type)
{
	t_token	*temp;

	temp = token;
	if (!temp)
		return (false);
	while (temp)
	{
		if (temp->type == type)
			return (true);
		temp = temp->next;
	}
	return (false);
}
