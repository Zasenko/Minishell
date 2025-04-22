/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibondarc <ibondarc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 14:24:36 by ibondarc          #+#    #+#             */
/*   Updated: 2025/02/17 14:24:36 by ibondarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	handle_heredoc(t_token *prev, char *input, int *i)
{
	int	start;

	start = *i;
	while (input[*i] && input[*i] != ' ' && input[*i] != '|' && input[*i] != '>'
		&& input[*i] != '<')
		(*i)++;
	prev->value = ft_substr(input, start, *i - start);
	if (!prev->value)
		return (false);
	prev->type = ARG;
	return (true);
}
