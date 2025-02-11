/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 13:44:19 by marvin            #+#    #+#             */
/*   Updated: 2025/02/10 13:44:19 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char **copy_env_into_2d_arr(char **envp)
{
    int i;
    int j;
    char **env_var;

    i = 0;
    while (envp[i] != NULL)
        i++;
    env_var = (char **)malloc((i + 1) * sizeof(char *));
    if (!env_var)
        return NULL;
    j = 0;
    env_var[i] = NULL;
    while (envp[j] != NULL)
    {
        env_var[j] = ft_strdup(envp[j]);
        if (!env_var[j])
            return NULL;
        j++;
    }
    return (env_var);
}
void copy_env(t_app *shell, char **envp)
{
    int     i;
    int     j;
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
                exit_with_error(shell, 1);
            name = ft_substr(s, 0, j);
            if (!name)
                exit_with_error(shell, 1);
            add_envp_back(&shell->envp, create_new_envp(env_var, name));
            i++;
        }
        shell->env_var = copy_env_into_2d_arr(envp);
        if (!shell->env_var)
            exit_with_error(shell, 1);
    }
}