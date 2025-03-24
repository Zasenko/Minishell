/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibondarc <ibondarc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 09:54:19 by dzasenko          #+#    #+#             */
/*   Updated: 2025/03/24 13:07:18 by ibondarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

typedef struct s_lib 
{
    char            *key;
    char            *value;
} t_lib;


int check_export_key(char *str)
{
    int i = 0;
    int len = ft_strlen(str);
    if (len == 0 || (len == 1 && !ft_isalpha(str[i])))
    {
        return (0);
    }
    else {
        while (str[i])
        {
            if (!ft_isprint(str[i]))
            {
                return (0);
            }
            else if (i == 0 && (!ft_isalpha(str[i]) && str[i] != '_'))
            {
                return (0);
            }
            else if (!ft_isalnum(str[i]) && str[i] != '_')
            {
                return (0);
            }
            i++;
        }   
    }
    return (1);
}

t_lib *check_export_arg(char *str, int *exit_code)
{
    char *temp = str;

    if (ft_strchr(temp, '=', false) == NULL)
    {
        if (!check_export_key(str))
        {
            ft_putstr_fd("export: `", 2);
            ft_putstr_fd(str, 2);
            ft_putstr_fd("': not a valid identifier\n", 2);
            *exit_code = 1;
            return (NULL);
        }

        t_lib *lib = ft_calloc(sizeof(t_lib), 1);
        if (!lib)
            return (NULL);
        char *new_key = ft_strdup(str);
        if (!new_key)
        {
            printf("check_export_arg ft_strdup error\n");
            free(lib);
            return NULL;
        }
        lib->key = new_key;
        lib->value = NULL;
        return (lib);
    }

    int i = 0;
    while (str[i] != '=')
        i++;
    char *key = (char *)ft_calloc(sizeof(char), i + 1);
    if (!key)
    {
        printf("malloc error\n");
        return (NULL);
    }
    ft_strlcpy(key, str, i + 1);
    if (!check_export_key(key))
    {
        ft_putstr_fd("export: `", 2);
        ft_putstr_fd(str, 2);
        ft_putstr_fd("': not a valid identifier\n", 2);
        *exit_code = 1;
        free(key);
        return NULL;
    }
    char *arg_value = ft_strchr(str, '=', true);
    char *value = NULL;
    if (!arg_value)
    {
        value = ft_strdup("");
        if (!value)
        {
            free(key);
            printf("ft_strdup error\n");
            return (NULL); 
        }
    }
    else {
        value = ft_strdup(arg_value);
        if (!value)
        {
            free(key);
            printf("ft_strdup error\n");
            return (NULL);
        }
    }
    t_lib *lib = ft_calloc(sizeof(t_lib), 1);
    if (!lib)
    {
        free(key);
        free(value);
        printf("ft_calloc error\n");
        return (NULL);            
    }
    lib->key = key;
    lib->value = value;
    return lib;
}

int ft_export(t_cmd *cmd, t_app *shell, bool is_child)
{
    struct s_envp *envp = shell->envp;
    int n = 1;

    int exit_code = 0;
    
    if (cmd->args[n] == NULL)
    {
        while (envp != NULL)
        {
            printf("declare -x ");
            printf("%s", envp->name);
            if (envp->envp)
            {
                printf("=\"");
                printf("%s\"", envp->envp);
            }
            printf("\n");
            envp = envp->next;
        }
    }
    else
    {
        while (cmd->args[n] != NULL)
        {
            t_lib *lib = check_export_arg(cmd->args[n], &exit_code);
            if (!lib)
            {
                
                shell->last_exit_code = exit_code;
                n++;
                continue;                
            }
            if (is_child)
            {
                if (lib->key)
                    free(lib->key);
                if (lib->value)
                    free(lib->value);
                free(lib);
                n++;
                continue;                
            }
            t_envp *node = find_envp_node(shell->envp, lib->key);
            if (!node)
            {
                t_envp *new = create_new_envp(lib->value, lib->key);
                if (!new)
                {
                    if (lib->key)
                        free(lib->key);
                    if (lib->value)
                        free(lib->value);
                    free(lib);
                    return (EXIT_FAILURE);
                }
                free(lib);
                add_envp_back(&shell->envp, new);
            }
            else
            {
                // printf("name: %s\n", node->name);
                // printf("envp: %s\n", node->envp);

                if (node->envp != NULL)
                {
                    free(node->envp);
                    node->envp = NULL;
                }
                node->envp = lib->value;

                if (lib->key)
                    free(lib->key);
                free(lib);
            }

            shell->is_envp_list_changed = true;
            n++;
        }
    }
    if (is_child)
    {
        exit(exit_code);
    }
    else
    {
        return(exit_code);
    }
}