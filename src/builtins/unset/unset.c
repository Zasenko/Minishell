/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzasenko <dzasenko@student.42.fr>          +#+  +:+       +#+        */
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

void	handle_node_unset(t_app *shell, t_envp *node)
{
	struct s_envp	*prev;
	struct s_envp	*next;

	prev = node->prev;
	next = node->next;
	if (next)
	{
		if (prev)
		{
			prev->next = next;
			next->prev = prev;
		}
	}
	else
	{
		if (prev)
		{
			prev->next = NULL;
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
			if (node)
				handle_node_unset(shell, node);
			i++;
		}
	}
	return (SUCCESS);
}

void	handle_copying_value(t_envp **curr, t_envp **next)
{
	if ((*curr)->prev)
		(*curr)->prev->next = *next;
	if (*next)
		(*next)->prev = (*curr)->prev;
	free((*curr)->name);
	free((*curr)->envp);
	free(*curr);
}

void	unset_env_values(t_app *shell, t_envp **envp)
{
	t_token	*token;
	t_envp	*curr;
	t_envp	*next;

	token = shell->tokens;
	while (token)
	{
		if (ft_strncmp(token->value, "unset", 5) == 0)
		{
			curr = *envp;
			while (curr != NULL)
			{
				next = curr->next;
				if (ft_strncmp(curr->name, token->next->value,
						ft_strlen(token->next->value)) == 0)
					handle_copying_value(&curr, &next);
				curr = next;
			}
		}
		token = token->next;
	}
}
