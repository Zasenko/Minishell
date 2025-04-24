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

t_lib *check_export_arg(char *str, int *exit_code, t_app *shell, bool is_child)
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
        {
            if (is_child)
				exit_child(shell, 1, NULL);
			exit_with_error(shell, 1, MALLOC_FAIL);
        }
        char *new_key = ft_strdup(str);
        if (!new_key)
        {
            free(lib);
            if (is_child)
				exit_child(shell, 1, NULL);
			exit_with_error(shell, 1, MALLOC_FAIL);
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
        if (is_child)
			exit_child(shell, 1, NULL);
		exit_with_error(shell, 1, MALLOC_FAIL);
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
            if (is_child)
				exit_child(shell, 1, NULL);
			exit_with_error(shell, 1, MALLOC_FAIL);
        }
    }
    else {
        value = ft_strdup(arg_value);
        if (!value)
        {
            free(key);
            if (is_child)
				exit_child(shell, 1, NULL);
			exit_with_error(shell, 1, MALLOC_FAIL);
        }
    }
    t_lib *lib = ft_calloc(sizeof(t_lib), 1);
    if (!lib)
    {
        free(key);
        free(value);
        if (is_child)
			exit_child(shell, 1, NULL);
		exit_with_error(shell, 1, MALLOC_FAIL);    
    }
    lib->key = key;
    lib->value = value;
    return lib;
}

void    sort_2d_env(char **env)
{
    int     i;
    int     sorted;
    char    *tmp;

    if (!env)
        return;
    sorted = 0;
    while (!sorted)
    {
        i = 0;
        sorted = 1;
        while (env[i] && env[i + 1])
        {
            if (ft_strcmp(env[i], env[i + 1]) > 0)
            {
                tmp = env[i];
                env[i] = env[i + 1];
                env[i + 1] = tmp;
                sorted = 0;
            }
            i++;
        }
    }
}

int ft_export(t_cmd *cmd, t_app *shell, bool is_child)
{
    struct s_envp *envp = shell->envp;
    int n = 1;

    int exit_code = 0;
    
    if (cmd->args[n] == NULL)
    {
        char **new_2d_env = copy_into_2d_arr(envp);
        if (!new_2d_env)
        {
            if (is_child)
                exit_child(shell, 1, NULL);
            exit_with_error(shell, 1, MALLOC_FAIL);
        }
        sort_2d_env(new_2d_env);

        int i = 0;
        while (new_2d_env[i])
        {
            if (new_2d_env[i][0] == '_')
            {
                i++;
                continue;
            }
            printf("declare -x "); 
            int g = 0;
            int f = 1;
            while (new_2d_env[i][g])
            {
                printf("%c", new_2d_env[i][g]);
                if (new_2d_env[i][g] == '=' && f)
                {
                    f = 0;
                    printf("%c", '"');
                }
                g++;
            }
            printf("%c", '"');
            printf("\n");
            i++;
        }
        free_2d_array(new_2d_env);
    }
    else
    {
        while (cmd->args[n] != NULL)
        {
            t_lib *lib = check_export_arg(cmd->args[n], &exit_code, shell, is_child);
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
                    if (is_child)
                        exit_child(shell, 1, NULL);
                    exit_with_error(shell, 1, MALLOC_FAIL);
                }
                free(lib);
                add_envp_back(&shell->envp, new);
            }
            else
            {
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
        exit_child(shell, exit_code, NULL);
    return(exit_code);
}
