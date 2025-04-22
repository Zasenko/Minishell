/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_memory.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibondarc <ibondarc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 21:24:31 by ibondarc          #+#    #+#             */
/*   Updated: 2025/02/03 21:24:31 by ibondarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_2d_array(char **arr)
{
	int	i;

	if (!arr)
		return ;
	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		arr[i] = NULL;
		i++;
	}
	free(arr);
}

void	free_prompt(t_app *shell)
{
	if (!shell)
		return ;
	if (shell->user)
	{
		free(shell->user);
		shell->user = NULL;
	}
	if (shell->name)
	{
		free(shell->name);
		shell->name = NULL;
	}
	if (shell->pwd)
	{
		free(shell->pwd);
		shell->pwd = NULL;
	}
	if (shell->prompt)
	{
		free(shell->prompt);
		shell->prompt = NULL;
	}
}
