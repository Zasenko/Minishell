/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzasenko <dzasenko@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 12:09:17 by dzasenko          #+#    #+#             */
/*   Updated: 2025/02/20 12:09:17 by dzasenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	free_node(t_envp *node)
{
	if (node)
	{
		if (node->envp)
		{
			free(node->envp);
		}
		if (node->name)
		{
			free(node->name);
		}
		free(node);
	}
}

void	handle_node_swap(t_app *shell, struct s_envp *prev, struct s_envp *next)
{
	if (prev)
	{
		prev->next = next;
		next->prev = prev;
	}
	else
	{
		next->prev = NULL;
		shell->envp = next;
	}
}

void	handle_node_unset(t_app *shell, t_envp *node)
{
	struct s_envp	*prev;
	struct s_envp	*next;

	prev = node->prev;
	next = node->next;
	if (next)
	{
		handle_node_swap(shell, prev, next);
	}
	else
	{
		if (prev)
		{
			prev->next = NULL;
		}
		else
		{
			shell->envp = NULL;
		}
	}
	free_node(node);
	shell->is_envp_list_changed = true;
}

int	ft_unset(t_cmd *cmd, t_app *shell, bool is_child)
{
	int		i;
	t_envp	*node;

	if (is_child)
		return (SUCCESS);
	i = 1;
	if (cmd->args[i] == NULL)
		return (SUCCESS);
	else
	{
		while (cmd->args[i])
		{
			node = find_envp_node(shell->envp, cmd->args[i]);
			if (node && node->name && ft_strcmp("_", node->name) != 0)
				handle_node_unset(shell, node);
			i++;
		}
	}
	return (SUCCESS);
}
