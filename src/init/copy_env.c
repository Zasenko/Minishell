/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibondarc <ibondarc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 13:44:19 by ibondarc          #+#    #+#             */
/*   Updated: 2025/02/10 13:44:19 by ibondarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	copy_env(t_app *shell, char **envp)
{
	int i;
	int j;
	char *name;
	char *env_var;
	char *s;

	i = 0;
	if (envp)
	{
		while (envp[i] != NULL)
		{
			j = 0;
			s = envp[i];
			while (s[j] != '=')
				j++;
			env_var = ft_strdup(ft_strchr(envp[i], '=', true));
			if (!env_var)
				break ;
			name = ft_substr(s, 0, j);
			if (!name)
				break ;
			add_envp_back(&shell->envp, create_new_envp(env_var, name));
			i++;
		}
	}
}
