/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_envp_node.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibondarc <ibondarc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 10:01:50 by dzasenko          #+#    #+#             */
/*   Updated: 2025/02/28 11:28:29 by ibondarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_envp *find_envp_node(t_envp *envp, char *key)
{
	t_envp	*temp;

	temp = envp;
	if (!temp)
		return (NULL);
	while (temp != NULL)
	{
		// printf("--temp->name-- %s\n", temp->name);
		// printf("--key-- %s\n", key);
        if (!ft_strncmp(temp->name, key, sizeof(key)))
        {
            return (temp);
        }
		temp = temp->next;
	}
	return (NULL);
}
