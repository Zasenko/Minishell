/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzasenko <dzasenko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 09:54:19 by dzasenko          #+#    #+#             */
/*   Updated: 2025/02/25 14:38:32 by dzasenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int ft_export(t_cmd *cmd, t_app *shell, bool is_child)
{
    struct s_envp *envp = shell->envp;
    
    if (cmd->args[1] == NULL)
    {
        while (envp != NULL)
        {
            printf("declare -x ");
            printf("%s", envp->name);
            printf("=\"");
            printf("%s\"\n", envp->envp);
            envp = envp->next;
        }
    }
    else
    {
        char *args = cmd->args[1];
        if (!ft_strchr(args, '=', false))
        {
            printf("ERROR in args = \n");
            return (EXIT_FAILURE);
        }
        if (is_child)
            return (SUCCESS);
        
        int i = 0;
        while (args[i] != '=')
            i++;
        
        char *new_name = (char *)ft_calloc(sizeof(char), i + 1);
        if (!new_name)
        {
            printf("malloc error\n");
            return (EXIT_FAILURE);
        }
        ft_strlcpy(new_name, args, i + 1);
        char *var = ft_strchr(args, '=', true);
        while (envp != NULL)
        {
            if (!ft_strncmp(envp->name, new_name, sizeof(args)))
            {
                if (!var)
                {
                    if (envp->envp != NULL)
                    {
                        free(envp->envp);
                        envp->envp = NULL;
                    }
                }
                else
                {
                    char *new_var = ft_strdup(var);
                    if (!new_var)
                    {
                        free(new_name);
                        printf("ERROR ft_strdup \n");
                        return (EXIT_FAILURE);
                    }
                    
                    if (envp->envp != NULL)
                    {
                        free(envp->envp);
                    }
                    envp->envp = new_var;
                }
                shell->is_envp_list_changed = true;
                return (SUCCESS);
            }
            envp = envp->next;
        }
        t_envp *new;

        if (!var)
        {
            new = create_new_envp(NULL, new_name);
            if (!new)
            {
                free(new_name);
                return (EXIT_FAILURE);
            }
        }
        else
        {
            char *new_var = ft_strdup(var);
            if (!new_var)
            {
                free(new_name);
                return (EXIT_FAILURE);
            }
            new = create_new_envp(new_var, new_name);
            if (!new)
            {
                free(new_var);
                free(new_name);
                return (EXIT_FAILURE);
            }
        }
        add_envp_back(&shell->envp, new);

        shell->is_envp_list_changed = true;
        return (SUCCESS);
    }
    return (SUCCESS);
}