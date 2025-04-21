/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing_inputs_date.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibondarc <ibondarc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 12:11:16 by ibondarc          #+#    #+#             */
/*   Updated: 2025/02/12 12:11:16 by ibondarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	handle_inputs(t_app *shell, t_token **head, char *input, int *i)
{
	t_token *last;

	while (input[*i])
	{
		if (!add_token_back(head, create_new_token()))
			return (false);
		skip_spases(input, i);
		if (ft_strchr("|<>", input[*i], false))
		{
			if (!handle_operators(last_token_node(*head), input, i))
				return (false);
		}
		else
		{
			last = last_token_node(*head);
			if (last->prev && last->prev->type == HEREDOC)
			{
				if (!handle_heredoc(last, input, i))
					return (false);
			}
			else if (!handle_command(shell, last, input, i))
				return (false);
		}
	}
	return (true);
}

bool	tokenize_data(t_app *shell, t_token *head, char *input)
{
	char *str;
	int i;

	i = 0;
	shell->is_valid_syntax = true;
	str = ft_strtrim(input, " \t");
	free(input);
	if (!str)
		return (false);
	if (!handle_inputs(shell, &head, str, &i))
		return (free(str), false);
	free(str);
	shell->tokens = head;
	if (!lexing_checker(shell))
		shell->is_valid_syntax = false;
	return (true);
}

void	lexing_inputs_data(t_app *shell, char *input)
{
	t_token *head;

	if (!shell)
		return ;
	head = NULL;
	if (!define_valid_string(input))
	{
		exit_with_error(shell, 1, QUOTE_ERR);
	}
	if (!tokenize_data(shell, head, input))
	{
		exit_with_error(shell, 1, MALLOC_FAIL);
	}
}
