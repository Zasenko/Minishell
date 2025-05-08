/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibondarc <ibondarc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 13:08:46 by ibondarc          #+#    #+#             */
/*   Updated: 2025/04/17 13:18:45 by ibondarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	write_value(t_token *token, char *value, int type)
{
	token->value = ft_strdup(value);
	if (!token->value)
		return ;
	token->type = type;
}

char	*divide_into_parts(char *input, int *i)
{
	bool	is_dq_open;
	bool	is_sq_open;
	int		start;

	start = *i;
	is_dq_open = false;
	is_sq_open = false;
	while (input[*i])
	{
		if (input[*i] == '\'' && !is_dq_open)
			is_sq_open = !is_sq_open;
		else if (input[*i] == '\"' && !is_sq_open)
			is_dq_open = !is_dq_open;
		else if ((input[*i] == '>' || input[*i] == '<' || input[*i] == ' '
				|| input[*i] == '\t' || input[*i] == '|') && !is_dq_open
			&& !is_sq_open)
			break ;
		(*i)++;
	}
	return (ft_substr(input, start, *i - start));
}

void	skip_all_beafor_variable(char *input, int *j)
{
	bool	sing_quote;
	bool	doub_quote;

	sing_quote = false;
	doub_quote = false;
	while (input[*j])
	{
		if (input[*j] == '\'' && !doub_quote)
			sing_quote = !sing_quote;
		if (input[*j] == '\"' && !sing_quote)
			doub_quote = !doub_quote;
		if (input[*j] == '$' && !sing_quote)
			break ;
		(*j)++;
	}
}

bool	handle_non_expansion(char **dest, char *input, int *j, int start)
{
	char	*temp;
	char	*res;

	temp = ft_substr(input, start, *j - start);
	if (!temp)
		return (false);
	res = ft_strjoin(*dest, temp);
	free(temp);
	if (!res)
		return (false);
	free(*dest);
	*dest = res;
	return (true);
}

bool	handle_expansion(char **dest, char *expanded, bool *do_split)
{
	char	*temp;

	if (ft_strchr(expanded, ' ', false))
		*do_split = true;
	temp = ft_strjoin(*dest, expanded);
	free(expanded);
	if (!temp)
		return (false);
	free(*dest);
	*dest = temp;
	return (true);
}
