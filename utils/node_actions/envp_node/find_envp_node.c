/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_envp_node.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzasenko <dzasenko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 10:01:50 by dzasenko          #+#    #+#             */
/*   Updated: 2025/03/21 12:25:32 by dzasenko         ###   ########.fr       */
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
        if (!ft_strncmp(temp->name, key, ft_strlen(key)))
        {
            return (temp);
        }
		temp = temp->next;
	}
	return (NULL);
}
