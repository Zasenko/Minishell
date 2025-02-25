/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzasenko <dzasenko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 09:54:19 by dzasenko          #+#    #+#             */
/*   Updated: 2025/02/25 13:35:16 by dzasenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int ft_export(t_cmd *cmd, t_app *shell)
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
        // printf("args = %s\n", args);

        if (!ft_strchr(args, '=', false))
        {
            printf("ERROR in args = \n");
            return (EXIT_FAILURE);
        }
        
        int i = 0;
        while (args[i] != '=')
            i++;
        // printf("i = %d\n", i);
        
        char *new_name = (char *)ft_calloc(sizeof(char), i + 1);
        if (!new_name)
        {
            printf("malloc error\n");
            return (EXIT_FAILURE);
        }
        ft_strlcpy(new_name, args, i + 1);
        // printf("new_name = %s\n", new_name);

        char *var = ft_strchr(args, '=', true);
        // printf("var = %s\n", var);

        
        while (envp != NULL)
        {
            // printf("--WHILE--\n");
            // printf("envp->name: %s\n", envp->name);
            // printf("new_name  : %s\n", new_name);

            if (!ft_strncmp(envp->name, new_name, sizeof(args)))
            {
                // printf("1111111111111111\n");
                if (!var)
                {
                    // printf("2222222222\n");
                    if (envp->envp != NULL)
                    {
                        printf("33333333333\n");
                        free(envp->envp);
                        envp->envp = NULL;
                    }
                }
                else
                {
                    // printf("44444444\n");
                    char *new_var = ft_strdup(var);
                    if (!new_var)
                    {
                        free(new_name);
                        printf("ERROR ft_strdup \n");
                        return (EXIT_FAILURE);
                    }
                    
                    if (envp->envp != NULL)
                    {
                        // printf("55555555555555\n");
                        free(envp->envp);
                    }
                    envp->envp = new_var;
                }
                shell->is_envp_list_changed = true;
                return (SUCCESS);
            }
            envp = envp->next;
        }
        // printf("00000000000000000000000000000000\n");
        t_envp *new;

        if (!var)
        {
            // printf("11111\n");

            new = create_new_envp(NULL, new_name);
            if (!new)
            {
                free(new_name);
                printf("create_new_envp error\n");
                return (EXIT_FAILURE);
            }
        }
        else
        {
            // printf("22222222\n");
            char *new_var = ft_strdup(var);
            if (!new_var)
            {
                free(new_name);
                printf("ERROR ft_strdup \n");
                return (EXIT_FAILURE);
            }
            new = create_new_envp(new_var, new_name);
            if (!new)
            {
                free(new_var);
                free(new_name);
                // printf("create_new_envp error\n");
                return (EXIT_FAILURE);
            }
        }

        // printf("var= %s\n", new->name);
        // printf("arg= %s\n", new->envp);
        
        add_envp_back(&shell->envp, new);

        shell->is_envp_list_changed = true;
        return (SUCCESS);
    }
    return (SUCCESS);
}