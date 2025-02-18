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

char **build_env_into_2d_arr(t_envp *envp)
{
    int     j;
    int     env_len;
    char    **env_var;
    char    *temp;

    env_len = get_envp_len(envp);
    env_var = (char **)malloc((env_len + 1) * sizeof(char *));
    if (!env_var)
        return NULL;
    j = 0;
    env_var[env_len] = NULL;
    while (envp != NULL)
    {
        temp = ft_strjoin(envp->name, "=");
        if (!temp)
            return NULL;
        env_var[j] = ft_strjoin(temp, envp->envp);
        if (!env_var[j])
            return NULL;
        envp = envp->next;
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
        shell->env_var = build_env_into_2d_arr(shell->envp);
        if (!shell->env_var)
            exit_with_error(shell, 1);
    }
}