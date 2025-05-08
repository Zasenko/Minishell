/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_new_envp.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibondarc <ibondarc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 14:01:24 by ibondarc          #+#    #+#             */
/*   Updated: 2025/02/10 14:01:24 by ibondarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_envp	*create_new_envp(char *envp, char *name)
{
	t_envp	*new;

	if (!name)
		return (NULL);
	new = malloc(sizeof(t_envp));
	if (!new)
		return (NULL);
	if (envp)
		new->envp = envp;
	else
		new->envp = NULL;
	new->name = name;
	new->prev = NULL;
	new->next = NULL;
	return (new);
}
