/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_memory.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 21:24:31 by marvin            #+#    #+#             */
/*   Updated: 2025/02/03 21:24:31 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void free_2d_arr(char **arr)
{
    int i;

    i = 0;
    while (arr[i])
    {
        free(arr[i]);
        arr[i] = NULL;
        i++;
    }
    free(arr);
}

void free_allocated_memory(t_app *shell)
{
    if (!shell)
        return ;
    if (shell->args || shell->args[0])
    {
        free_2d_arr(shell->args);
    }
    if (shell->path || shell->path[0])
    {
        free_2d_arr(shell->path);
    }
	if (shell->user)
        free(shell->user);
	if (shell->name)
        free(shell->name);
    if (shell->pwd)
        free(shell->pwd);
    
}
