/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzasenko <dzasenko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 09:59:49 by dzasenko          #+#    #+#             */
/*   Updated: 2025/03/03 15:17:59 by dzasenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int arr2d_len(char **arr)
{
    int i = 0;
    if (!arr)
        return 0;
    while (arr[i])
        i++;
    return (i);
}

// int check_exit_arg(char *arg)
// {
//     int i;
//     char *trimmed;
    
//     i = 0;
//     trimmed = ft_strtrim(arg, " \t");
//     if (!trimmed)
//         return (1);
            
//     if (trimmed[i] == '+' || trimmed[i] == '-')
//          i++;
//     if (ft_strlen(&trimmed[i]) < 1)
//     {
//         ft_putstr_fd("exit: ", 2);
//         ft_putstr_fd(arg, 2);
//         ft_putstr_fd(": numeric argument required\n", 2);
//         free(trimmed);
//         return (2);
//     }
//     while (trimmed[i])
//     {
//         if (!ft_isdigit(trimmed[i]))
//         {
//             ft_putstr_fd("exit: ", 2);
//             ft_putstr_fd(arg, 2);
//             ft_putstr_fd(": numeric argument required\n", 2);
//             free(trimmed);
//             return (2);
//         }
//         i++;
//     }
//     free(trimmed);
//     return (0);
// }

// int check_exit_args(char **args, t_app *shell)
// {
//     int i;

//     i = 1;
//     while (args[i])
//     {
//         int result = check_exit_arg(args[i]);
//         if (result != 0)
//         {
//             if (result == 1)
//             {
//                 free_list(shell);
//                 exit(1);
//             }
//             shell->last_exit_code = result;
//             return 1;
//         }
//         i++;        
//     }
// }

int ft_exit(t_cmd *cmd, t_app *shell, int is_parent)
{
    int exit_code;

    exit_code = 0;

    if (arr2d_len(cmd->args) > 2)
    {
        ft_putstr_fd("exit: too many arguments\n", 2);
        
        shell->last_exit_code = 130;
        return 130;
    }

    else if (arr2d_len(cmd->args) == 1)
    {
        printf("exit\n");
        if (is_parent)
        {
            // free_envp_list(&shell->envp);
            free_list(shell);
            exit(shell->last_exit_code);
        }
        else
            exit(shell->last_exit_code);
    }
    else
    {
        char *trimmed = ft_strtrim(cmd->args[1], " \t");  
        if (!trimmed)
        {
            if (is_parent)
            {
                // free_envp_list(&shell->envp);
                free_list(shell);
                exit(1);
            }
            else
                exit(1);
        }
        int i = 0;
        if (trimmed[i] == '+' || trimmed[i] == '-')
            i++;
        if (ft_strlen(&trimmed[i]) < 1)
        {
            ft_putstr_fd("exit: ", 2);
            ft_putstr_fd(cmd->args[1], 2);
            ft_putstr_fd(": numeric argument required\n", 2);
            // printf("exit\n");
            // printf("bash: exit: %s: numeric argument required\n", trimmed);
            free(trimmed);
            if (is_parent)
            {
                free_list(shell);
                exit(2);
            }
            else
                exit(2);
        }

        while (trimmed[i])
        {
            if (!ft_isdigit(trimmed[i]))
            {
            ft_putstr_fd("exit: ", 2);
            ft_putstr_fd(cmd->args[1], 2);
            ft_putstr_fd(": numeric argument required\n", 2);
                free(trimmed);
                if (is_parent)
                {
                    free_list(shell);
                    exit(2);
                }
                else
                    exit(2);
                }
            i++;
        }
        exit_code = ft_atoi(trimmed);
        free(trimmed);
        printf("exit\n");
        if (is_parent)
        {
            free_list(shell);
            exit(exit_code);
        }
        else
            exit(exit_code);
    }

}