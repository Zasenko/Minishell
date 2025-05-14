/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibondarc <ibondarc@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 11:25:59 by dzasenko          #+#    #+#             */
/*   Updated: 2025/05/14 11:54:35 by ibondarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	add_new_envp(t_app *shell, t_lib **lib)
{
	t_envp	*new;

	new = create_new_envp((*lib)->value, (*lib)->key);
	if (!new)
		return (0);
	add_envp_back(&shell->envp, new);
	return (1);
}

int	create_node(t_app *shell, t_lib **lib)
{
	t_envp	*node;

	node = find_envp_node(shell->envp, (*lib)->key);
	if (!node)
	{
		if (!add_new_envp(shell, lib))
			return (0);
	}
	else
	{
		if (node->envp != NULL && (*lib)->value == NULL)
			return (free_lib_list(lib), 1);
		if (node->envp != NULL)
		{
			free(node->envp);
			node->envp = NULL;
		}
		node->envp = (*lib)->value;
		if ((*lib)->key)
			free((*lib)->key);
	}
	free(*lib);
	*lib = NULL;
	return (1);
}
