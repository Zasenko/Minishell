/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzasenko <dzasenko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 09:49:08 by dzasenko          #+#    #+#             */
/*   Updated: 2025/02/20 15:15:38 by dzasenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int ft_echo(char **args)
{
    int i;
    bool with_new_line;

    with_new_line = true;
    if (!args || !*args)
    {
        ft_putstr_fd("\n", 1);
        return (1);
    }
    
    i = 1;
    while (args[i])
    {
        if (!ft_strncmp(args[i], "-n", 2))
        {
            with_new_line = false;
            i++;
        }
        else {
            break;
        }
    }
    while (args[i])
    {
        ft_putstr_fd(args[i], 1);
        if (args[i + 1] != NULL)
            ft_putstr_fd(" ", 1);
        i++;   
    }
    if (with_new_line == false)
    {
        char c = 37;
        write(1, &c, 1);
    }
    ft_putstr_fd("\n", 1);
    return (1);
}
