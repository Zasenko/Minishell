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

int ft_echo(char **args)
{
    int i;
    bool with_new_line;

    with_new_line = true;
    if (!args || !*args)
    {
        printf("\n");
        return (EXIT_SUCCESS);
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
        printf("%s", args[i]);
        if (args[i + 1] != NULL)
            printf(" ");
        i++;   
    }
    if (with_new_line == true)
    {
        printf("\n");
    }
    return (EXIT_SUCCESS);
}
