/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibondarc <ibondarc@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 09:54:19 by dzasenko          #+#    #+#             */
/*   Updated: 2025/03/24 13:07:18 by ibondarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	show_export(char **str, int *i, int *g)
{
	while (str[*i])
	{
		if (str[*i][0] == '_')
		{
			(*i)++;
			continue ;
		}
		printf("declare -x ");
		*g = 0;
		handle_export_showing(str, i, g);
		printf("\n");
		(*i)++;
	}
}

int	create_node(t_app *shell, t_lib **lib)
{
	t_envp	*node;
	t_envp	*new;

	node = find_envp_node(shell->envp, (*lib)->key);
	if (!node)
	{
		new = create_new_envp((*lib)->value, (*lib)->key);
		if (!new)
			return (0);
		add_envp_back(&shell->envp, new);
	}
	else
	{
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

int	create_export_list(t_app *shell, t_cmd *cmd, int *exit_code, bool is_child)
{
	int		n;
	t_lib	*lib;

	n = 1;
	while (cmd->args[n] != NULL)
	{
		lib = check_export_arg(cmd->args[n], exit_code, shell, is_child);
		if (!lib)
		{
			shell->last_exit_code = *exit_code;
			n++;
			continue ;
		}
		if (is_child)
		{
			free_lib_list(&lib);
			n++;
			continue ;
		}
		if (!create_node(shell, &lib))
			return (free_lib_list(&lib), 0);
		shell->is_envp_list_changed = true;
		n++;
	}
	return (1);
}

bool	handle_export(t_app *shell, t_cmd *cmd, int *exit_code, bool is_child)
{
	struct s_envp	*envp;
	char			**new_2d_env;
	int				i;
	int				g;

	i = 0;
	envp = shell->envp;
	if (cmd->args[1] == NULL)
	{
		new_2d_env = copy_into_2d_arr(envp);
		if (!new_2d_env)
			return (0);
		sort_2d_env(new_2d_env);
		show_export(new_2d_env, &i, &g);
		free_2d_array(new_2d_env);
	}
	else
	{
		return (create_export_list(shell, cmd, exit_code, is_child));
	}
	return (1);
}

int	ft_export(t_cmd *cmd, t_app *shell, bool is_child)
{
	int	exit_code;
	int	res;

	exit_code = 0;
	res = handle_export(shell, cmd, &exit_code, is_child);
	if (!res && is_child)
		exit_child(shell, exit_code, NULL);
	else if (!res && !is_child)
		exit_with_error(shell, 1, MALLOC_FAIL);
	return (exit_code);
}
