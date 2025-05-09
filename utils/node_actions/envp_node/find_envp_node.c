/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_envp_node.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibondarc <ibondarc@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 10:01:50 by dzasenko          #+#    #+#             */
/*   Updated: 2025/03/24 13:26:44 by ibondarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_envp	*find_envp_node(t_envp *envp, char *key)
{
	t_envp	*temp;

	temp = envp;
	if (!temp)
		return (NULL);
	while (temp != NULL)
	{
		if (!ft_strcmp(temp->name, key))
		{
			return (temp);
		}
		temp = temp->next;
	}
	return (NULL);
}
