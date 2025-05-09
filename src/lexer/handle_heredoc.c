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
	char	*part;

	part = divide_into_parts(input, i);
	if (!part)
		return (false);
	prev->value = part;
	prev->type = ARG;
	return (true);
}
