/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_operators.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibondarc <ibondarc@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 15:31:31 by ibondarc          #+#    #+#             */
/*   Updated: 2025/02/17 15:31:31 by ibondarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_type	define_operator(char *input, int *i)
{
	if (input[*i] == '|')
		return (PIPE);
	if (input[*i] == '<')
	{
		if (input[*i + 1] == '<')
			return (HEREDOC);
		else
			return (REDIR_IN);
	}
	if (input[*i] == '>')
	{
		if (input[*i + 1] == '>')
			return (APPEND);
		else
			return (REDIR_OUT);
	}
	return (ERROR);
}

bool	handle_operators(t_token *token, char *input, int *i)
{
	token->type = define_operator(input, i);
	if (token->type != APPEND && token->type != HEREDOC)
	{
		token->value = ft_substr(input, (*i)++, 1);
		if (!token->value)
			return (false);
	}
	else
	{
		token->value = ft_substr(input, (*i)++, 2);
		if (!token->value)
			return (false);
		(*i)++;
	}
	return (true);
}
