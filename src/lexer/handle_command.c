/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibondarc <ibondarc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 15:47:48 by ibondarc          #+#    #+#             */
/*   Updated: 2025/02/17 15:47:48 by ibondarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	join_partitions(t_app *shell, char **dest, char *input, bool *do_split)
{
	char *expanded;
	int j;
	int start;

	j = 0;
	*dest = ft_strdup("");
	if (!(*dest))
		return (false);
	while (input[j])
	{
		start = j;
		skip_all_beafor_variable(input, &j);
		if (start != j)
			if (!handle_non_expansion(dest, input, &j, start))
				return (false);
		if (input[j] == '$')
		{
			expanded = expand_words(shell, input, &j);
			if (!expanded)
				return (false);
			if (!handle_expansion(dest, expanded, do_split))
				return (false);
		}
	}
	return (true);
}

bool	handle_redir_outfile(t_app *shell, t_token *token, char *input,
		bool *do_split)
{
	int j;
	char **temp;
	char *result;

	j = 0;
	result = NULL;
	if (!join_partitions(shell, &result, input, do_split))
		return (free(input), free(result), false);
	temp = ft_split(result, ' ');
	if (!temp)
		return (free(input), false);
	while (temp[j])
		j++;
	if (j == 0 || j > 1 || !ft_strlen(temp[0]))
	{
		ft_putstr_fd(input, 2);
		ft_putstr_fd(": ambiguous redirect\n", 2);
		shell->last_exit_code = 1;
	}
	token->value = result;
	token->type = ARG;
	free_2d_array(temp);
    free(input);
	return (true);
}

bool	add_expanded_value_into_node(t_token *token, char **input)
{
	int j;
	t_token *new;

	j = 0;
	if (!input)
		return (false);
	while (input[j])
	{
		if (j == 0)
			write_value(token, input[j], ARG);
		else
		{
			new = create_new_token();
			if (!new)
				return (free_2d_array(input), false);
			write_value(new, input[j], ARG);
			add_token_back(&token, new);
		}
		j++;
	}
	free_2d_array(input);
	return true;
}

bool	handle_quotes_case(t_app *shell, t_token *token, char *part)
{
	bool do_split;
	char **temp;

	do_split = false;
	if (define_valid_string(part))
	{
		if (!join_partitions(shell, &token->value, part, &do_split))
            return (false);
		if (do_split)
		{
			temp = ft_split(token->value, ' ');
			if (!add_expanded_value_into_node(token, temp))
                return (false);
		}
	}
	else
	{
		token->value = ft_strdup(part);
		if (!token->value)
			return (false);
	}
	token->type = ARG;
    free(part);
	return true;
}

bool	handle_command(t_app *shell, t_token *token, char *input, int *i)
{
	char *part;
	char *result;
	bool do_split;
	char **temp;

	do_split = false;
	result = NULL;
	part = divide_into_parts(input, i);
	if (!part)
		return false;
	if (!ft_strchr(part, '$', false))
		return (write_value(token, part, ARG), free(part), true);
	else if (ft_strchr(part, '\"', false) || ft_strchr(part, '\'', false))
		return (handle_quotes_case(shell, token, part));
	else if (token->prev && token->prev->type == REDIR_OUT)
		return (handle_redir_outfile(shell, token, part, &do_split));
	else if (!join_partitions(shell, &result, part, &do_split))
		return (free(part), free(result), false);
	temp = ft_split(result, ' ');
	free(result);
	if (!add_expanded_value_into_node(token, temp))
		return (free(part), false);
	free(part);
	return true;
}
