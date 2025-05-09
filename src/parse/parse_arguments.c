/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_arguments.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibondarc <ibondarc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 16:35:06 by ibondarc          #+#    #+#             */
/*   Updated: 2025/02/23 16:35:06 by ibondarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	handle_arguments(char **result, t_token **token, int *i)
{
	if ((*token)->type == REDIR_IN || (*token)->type == REDIR_OUT
		|| (*token)->type == APPEND || (*token)->type == HEREDOC)
		*token = (*token)->next;
	else if ((*token)->type == ARG)
	{
		if ((*token)->next && !ft_strlen((*token)->value))
		{
			result[*i] = ft_strdup((*token)->next->value);
			if (!result[*i])
				return (false);
			*token = (*token)->next;
		}
		else
		{
			result[*i] = extract_word_from_quotes((*token)->value);
			if (!result[*i])
				return (false);
		}
		(*i)++;
	}
	return (true);
}

bool	validate_file_name(t_token **token, t_redir **redir)
{
	if ((*token)->next && (*token)->next->is_ambiguous)
	{
		(*redir)->is_ambiguous = true;
		(*redir)->err_name = ft_strdup((*token)->next->err_name);
		if (!(*redir)->err_name)
			return (false);
	}
	return (true);
}

char	**extract_arguments(t_token *token)
{
	int		i;
	int		args_count;
	char	**result;

	args_count = count_types(token, ARG) + 1;
	result = ft_calloc(args_count, sizeof(char *));
	if (!result)
		return (NULL);
	i = 0;
	while (token && i < args_count)
	{
		if (token->type == PIPE)
			break ;
		if (!handle_arguments(result, &token, &i))
			return (false);
		token = token->next;
	}
	return (result);
}

bool	parse_arguments(t_app *shell, t_cmd *cmd, t_token *token,
		bool *iswriten)
{
	cmd->is_valid_cmd = true;
	cmd->args = extract_arguments(token);
	if (!cmd->args)
		return (false);
	cmd->cmd = parse_command(shell, cmd, cmd->args[0]);
	if (!cmd->cmd)
		return (false);
	*iswriten = false;
	return (true);
}
