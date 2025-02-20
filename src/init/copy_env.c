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

void build_env_into_2d_arr(t_app *shell)
{
    int     i;
    char    **env_var;
    char    *temp;
    t_envp  *envp;

    if (!shell || !shell->envp)
        return ;
    envp = shell->envp;
    i = get_envp_len(envp);
    env_var = (char **)malloc((i + 1) * sizeof(char *));
    if (!env_var)
        return ;
    env_var[i] = NULL;
    i = 0;
    while (envp != NULL)
    {
        temp = ft_strjoin(envp->name, "=");
        if (!temp)
            return ;
        env_var[i] = ft_strjoin(temp, envp->envp);
        free(temp);
        if (!env_var[i])
            return ;
        envp = envp->next;
        i++;
    }
    shell->env_var = env_var;
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
                break ;
            name = ft_substr(s, 0, j);
            if (!name)
                break;
            add_envp_back(&shell->envp, create_new_envp(env_var, name));
            i++;
        }
    }
}