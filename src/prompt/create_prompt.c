/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_prompt.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibondarc <ibondarc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 20:28:34 by ibondarc          #+#    #+#             */
/*   Updated: 2025/02/05 20:28:34 by ibondarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	handle_creating_prompt(char **prompt, char **parts)
{
	char	*temp;
	int		i;

	i = 0;
	while (i < 8)
	{
		temp = ft_strjoin(*prompt, parts[i]);
		free(*prompt);
		if (!temp)
			return (false);
		*prompt = temp;
		i++;
	}
	return (true);
}

void	create_prompt_path(t_app *shell)
{
	char	*prompt;
	char	*parts[8];

	if (!get_env_info(shell))
		exit_with_error(shell, 1, QUOTE_ERR);
	prompt = ft_strjoin(GREEN, shell->name);
	if (!prompt)
		exit_with_error(shell, 1, QUOTE_ERR);
	parts[0] = "@";
	parts[1] = shell->user;
	parts[2] = RESET;
	parts[3] = ":";
	parts[4] = BLUE;
	parts[5] = shell->pwd;
	parts[6] = RESET;
	parts[7] = "$ ";
	if (!handle_creating_prompt(&prompt, parts))
	{
		exit_with_error(shell, 1, QUOTE_ERR);
	}
	shell->prompt = prompt;
}
