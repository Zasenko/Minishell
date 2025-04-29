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

#include "../../../includes/minishell.h"

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


void show_export_without_env(char  **str)
{
    int i;
    
    i = 0;
    while (str[i])
    {
        if (str[i][0] == '_')
        {
            i++;
            continue;
        }
        printf("declare -x "); 
        int g = 0;
        int f = 1;
        while (str[i][g])
        {
            printf("%c", str[i][g]);
            if (str[i][g] == '=' && f)
            {
                f = 0;
                printf("%c", '"');
            }
            g++;
        }
        printf("%c\n", '"');
        i++;
    }
}

void free_lib_list(t_lib **lib)
{
    if (!lib)
        return;
    if ((*lib)->key)
    {
        free((*lib)->key);
        (*lib)->key = NULL;
    }
    if ((*lib)->value)
    {
        free((*lib)->value);
        (*lib)->value = NULL;
    }
    free(*lib);
    *lib = NULL;
}

int create_node(t_app *shell, t_lib **lib)
{
    t_envp *node;
    t_envp *new;

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
    return 1;
}

int create_export_list(t_app *shell, t_cmd *cmd, int *exit_code, bool is_child)
{
    int     n;
    t_lib   *lib;

    n = 1;
    while (cmd->args[n] != NULL)
    {
        lib = check_export_arg(cmd->args[n], exit_code, shell, is_child);
        if (!lib)
        {
            shell->last_exit_code = *exit_code;
            n++;
            continue;                
        }
        if (is_child)
        {
            free_lib_list(&lib);
            n++;
            continue;                
        }
        if (!create_node(shell, &lib))
            return (free_lib_list(&lib), 0);
        shell->is_envp_list_changed = true;
        n++;
    }
    return 1;
}

bool handle_export(t_app *shell, t_cmd *cmd, int *exit_code, bool is_child)
{
    struct s_envp   *envp;
    char            **new_2d_env;
 
    envp = shell->envp;
    if (cmd->args[1] == NULL)
    {
        new_2d_env = copy_into_2d_arr(envp);
        if (!new_2d_env)
            return (0);
        sort_2d_env(new_2d_env);
        show_export_without_env(new_2d_env);
        free_2d_array(new_2d_env);
    }
    else
    {
        return create_export_list(shell, cmd, exit_code, is_child);
    }
    return (1);
}

int ft_export(t_cmd *cmd, t_app *shell, bool is_child)
{
    int             exit_code;
    int             res;
    
    exit_code = 0;
    res = handle_export(shell, cmd, &exit_code, is_child);
    if (!res && is_child) 
        exit_child(shell, exit_code, NULL);
    else if (!res && !is_child)
        exit_with_error(shell, 1, MALLOC_FAIL);
    return(exit_code);
}
