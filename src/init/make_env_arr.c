/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_env_arr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibondarc <ibondarc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 11:25:07 by ibondarc          #+#    #+#             */
/*   Updated: 2025/04/14 11:56:47 by ibondarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*make_copy(t_envp *envp)
{
	char	*temp;
	char	*res;

	if (!envp)
		return (NULL);
	if (!envp->envp && envp->name)
	{
		res = strdup(envp->name);
		if (!res)
			return (NULL);
	}
	else
	{
		temp = ft_strjoin(envp->name, "=");
		if (!temp)
			return (NULL);
		res = ft_strjoin(temp, envp->envp);
		free(temp);
		temp = NULL;
		if (!res)
			return (NULL);
	}
	return (res);
}

char	**copy_into_2d_arr(t_envp *envp)
{
	int		i;
	char	**env_var;

	if (!envp)
		return (NULL);
	i = get_envp_len(envp);
	env_var = (char **)malloc((i + 1) * sizeof(char *));
	if (!env_var)
		return (NULL);
	env_var[i] = NULL;
	i = 0;
	while (envp != NULL)
	{
		env_var[i] = make_copy(envp);
		if (!env_var[i])
			return (free_2d_array(env_var), NULL);
		envp = envp->next;
		i++;
	}
	return (env_var);
}

void	build_env_into_2d_arr(t_app *shell)
{
	if (!shell)
		return ;
	shell->env_var = copy_into_2d_arr(shell->envp);
	if (!shell->env_var)
	{
		exit_with_error(shell, 1, MALLOC_FAIL);
	}
}
