/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzasenko <dzasenko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 09:49:08 by dzasenko          #+#    #+#             */
/*   Updated: 2025/02/24 13:00:15 by dzasenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int ft_echo(char **args, int fd)
{
    int i;
    bool with_new_line;

    with_new_line = true;
    if (!args || !*args)
    {
        ft_putstr_fd("\n", fd);
        return (EXIT_SUCCESS);
    }
    
    i = 1;
    while (args[i])
    {
        if (!ft_strncmp(args[i], "-n", 2))
        {
            int d = 2;
            while (args[i][d] && args[i][d] == 'n')
            {
                d++;
            }
            if (args[i][d] == '\0') {
                with_new_line = false;
                i++;
            }
            else {
                break;
            }
        }
        else {
            break;
        }
    }
    while (args[i])
    {
        ft_putstr_fd(args[i], fd);
        if (args[i + 1] != NULL)
            ft_putstr_fd(" ", fd);
        i++;   
    }
    if (with_new_line == true)
    {
        ft_putstr_fd("\n", fd);
    }
    return (EXIT_SUCCESS);
}
