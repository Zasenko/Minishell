/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibondarc <ibondarc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 09:54:19 by dzasenko          #+#    #+#             */
/*   Updated: 2025/02/28 13:21:58 by ibondarc         ###   ########.fr       */
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
        printf("not a valid identifier\n");
        return (0);
    }
    else {
        while (str[i])
        {
            if (!ft_isprint(str[i]))
            {
                printf("not a valid identifier\n");
                return (0);
            }
            else if (i == 0 && (!ft_isalpha(str[i]) && str[i] != '_'))
            {
                printf("not a valid identifier\n");
                return (0);
            }
            else if (!ft_isalnum(str[i]) && str[i] != '_')
            {
                printf("not a valid identifier\n");
                return (0);
            }
            i++;
        }   
    }
    return (1);
}

t_lib *check_export_arg(char *str)
{
    if (!ft_strchr(str, '=', false))
    {
        if (!check_export_key(str))
            return (NULL);
        t_lib *lib = ft_calloc(sizeof(t_lib), 1);
        if (!lib)
            return (NULL);
        lib->key = str;
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
    printf("EXPORT key: %s\n", key);
    if (!check_export_key(key))
    {
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
        // free(key);
        // printf("ft_strdup error\n");
        // return (NULL);
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
            t_lib *lib = check_export_arg(cmd->args[n]);
            if (!lib)
            {
                shell->last_exit_code = 1;
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

            // printf("key---- %s\n", lib->key);
            // printf("value---- %s\n", lib->value);
            
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
                // printf("new1---- %s\n", new->name);
                // printf("new2---- %s\n", new->envp);
                // printf("------------------------------------------\n");
                // print_envp2(shell->envp);
                // printf("------------------------------------------\n");

            }
            else
            {
                // printf("node->envp: %s\n", node->envp);
                // printf("node->name: %s\n", node->name);
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
    return (SUCCESS);
}

// int ft_export2(t_cmd *cmd, t_app *shell, bool is_child)
// {
//     struct s_envp *envp = shell->envp;
//     int n = 1;
    
//     if (cmd->args[n] == NULL)
//     {
//         while (envp != NULL)
//         {
//             printf("declare -x ");
//             printf("%s", envp->name);
//             printf("=\"");
//             printf("%s\"\n", envp->envp);
//             envp = envp->next;
//         }
//     }
//     else
//     {
//         char *args = cmd->args[n];
//         if (!ft_strchr(args, '=', false))
//         {
//             printf("ERROR in args = \n");
//             return (EXIT_FAILURE);
//         }
//         if (is_child)
//             return (SUCCESS);
        
//         int i = 0;
//         while (args[n] != '=')
//             i++;
        
//         char *new_name = (char *)ft_calloc(sizeof(char), i + 1);
//         if (!new_name)
//         {
//             printf("malloc error\n");
//             return (EXIT_FAILURE);
//         }
//         ft_strlcpy(new_name, args, i + 1);
//         char *var = ft_strchr(args, '=', true);
//         while (envp != NULL)
//         {
//             if (!ft_strncmp(envp->name, new_name, sizeof(args)))
//             {
//                 if (!var)
//                 {
//                     if (envp->envp != NULL)
//                     {
//                         free(envp->envp);
//                         envp->envp = NULL;
//                     }
//                 }
//                 else
//                 {
//                     char *new_var = ft_strdup(var);
//                     if (!new_var)
//                     {
//                         free(new_name);
//                         printf("ERROR ft_strdup \n");
//                         return (EXIT_FAILURE);
//                     }
                    
//                     if (envp->envp != NULL)
//                     {
//                         free(envp->envp);
//                     }
//                     envp->envp = new_var;
//                 }
//                 shell->is_envp_list_changed = true;
//                 return (SUCCESS);
//             }
//             envp = envp->next;
//         }
//         t_envp *new;

//         if (!var)
//         {
//             new = create_new_envp(NULL, new_name);
//             if (!new)
//             {
//                 free(new_name);
//                 return (EXIT_FAILURE);
//             }
//         }
//         else
//         {
//             char *new_var = ft_strdup(var);
//             if (!new_var)
//             {
//                 free(new_name);
//                 return (EXIT_FAILURE);
//             }
//             new = create_new_envp(new_var, new_name);
//             if (!new)
//             {
//                 free(new_var);
//                 free(new_name);
//                 return (EXIT_FAILURE);
//             }
//         }
//         add_envp_back(&shell->envp, new);

//         shell->is_envp_list_changed = true;

//         n++;
        
        
//         while (cmd->args[n] != NULL)
//         {
//             char *argsN = cmd->args[n];
//             if (ft_strchr(argsN, '=', false) != NULL)
//             {
//                 int f = 0;
//                 while (argsN[n] != '=')
//                     f++;
        
//                 char *new_name2 = (char *)ft_calloc(sizeof(char), f + 1);
//                 if (!new_name2)
//                 {
//                     printf("malloc error\n");
//                     return (EXIT_FAILURE);
//                 }
//                 ft_strlcpy(new_name2, argsN, f + 1);
//                 char *var2 = ft_strchr(argsN, '=', true);
//                 envp = shell->envp;
//                 while (envp != NULL)
//                 {
//                     if (!ft_strncmp(envp->name, new_name2, sizeof(argsN)))
//                     {
//                         if (!var2)
//                         {
//                             if (envp->envp != NULL)
//                             {
//                                 free(envp->envp);
//                                 envp->envp = NULL;
//                             }
//                         }
//                         else
//                         {
//                             char *new_var2 = ft_strdup(var2);
//                             if (!new_var2)
//                             {
//                                 free(new_name2);
//                                 printf("ERROR ft_strdup \n");
//                                 return (EXIT_FAILURE);
//                             }
                    
//                             if (envp->envp != NULL)
//                             {
//                                 free(envp->envp);
//                             }
//                             envp->envp = new_var2;
//                         }
//                         shell->is_envp_list_changed = true;
//                         break;;
//                     }
//                     envp = envp->next;
//                 }
//         t_envp *new;

//         if (!var)
//         {
//             new = create_new_envp(NULL, new_name);
//             if (!new)
//             {
//                 free(new_name);
//                 return (EXIT_FAILURE);
//             }
//         }
//         else
//         {
//             char *new_var = ft_strdup(var);
//             if (!new_var)
//             {
//                 free(new_name);
//                 return (EXIT_FAILURE);
//             }
//             new = create_new_envp(new_var, new_name);
//             if (!new)
//             {
//                 free(new_var);
//                 free(new_name);
//                 return (EXIT_FAILURE);
//             }
//         }
//         add_envp_back(&shell->envp, new);

//             }

//             n++;
//         }
        
//         return (SUCCESS);
//     }
//     return (SUCCESS);
// }