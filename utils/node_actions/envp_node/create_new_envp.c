/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_new_envp.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 14:01:24 by marvin            #+#    #+#             */
/*   Updated: 2025/02/10 14:01:24 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_envp *create_new_envp(char *envp, char *name)
{
	t_envp *new;
	
	new = malloc(sizeof(t_envp));
	if (!new)
		return NULL;
	new->envp = envp;
	new->name = name;
	new->prev = NULL;
	new->next = NULL;
	return new;
}