/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 10:21:50 by marvin            #+#    #+#             */
/*   Updated: 2025/02/13 10:21:50 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	handle_redir_parsing(t_cmd **cmd, t_token **token, t_type type)
{
	t_redir *redir;

	redir = create_new_redir();
	if (!redir)
		return (false);
	if (is_there_quote((*token)->next->value))
	{
		redir->type = type;
		redir->value = extract_word_from_quotes((*token)->next->value);
		if (!redir->value)
			return (false);
	}
	else
	{
		redir->type = type;
		redir->value = ft_strdup((*token)->next->value);
		if (!redir->value)
			return (false);
	}
	add_redir_back(&(*cmd)->redirs, redir);
	*token = (*token)->next;
	return (true);
}

bool	handle_heredoc_parsing(t_cmd **cmd, t_token **token, t_type type)
{
	t_redir *redir;

	redir = create_new_redir();
	if (!redir)
		return (false);
	if (is_there_quote((*token)->next->value))
	{
		redir->type = type;
		redir->heredock_with_quotes = true;
		redir->stop_word = extract_word_from_quotes((*token)->next->value);
		if (!redir->stop_word)
			return (false);
	}
	else
	{
		redir->type = type;
		redir->stop_word = ft_strdup((*token)->next->value);
		if (!redir->stop_word)
			return (false);
	}
	add_redir_back(&(*cmd)->redirs, redir);
	*token = (*token)->next;
	return (true);
}

bool	handle_pipe(t_cmd **head, t_cmd **cmd, bool *iswriten)
{
	add_cmd_back(head, *cmd);
	*cmd = create_new_cmd();
	if (!(*cmd))
		return (false);
	*iswriten = true;
	return (true);
}
bool	handle_token_parsing(t_app *shell, t_cmd **head, t_cmd **cmd,
		bool *iswriten)
{
	t_token *token;

	token = shell->tokens;
	while (token != NULL)
	{
		if (token->type == ARG && *iswriten)
			if (!parse_arguments(shell, *cmd, token, iswriten))
				return (false);
		if (token->type == PIPE && token->next)
			if (!handle_pipe(head, cmd, iswriten))
				return (false);
		if (token->type == REDIR_IN && token->next)
			if (!handle_redir_parsing(cmd, &token, REDIR_IN))
				return (false);
		if (token->type == REDIR_OUT && token->next)
			if (!handle_redir_parsing(cmd, &token, REDIR_OUT))
				return (false);
		if (token->type == APPEND)
			if (!handle_redir_parsing(cmd, &token, APPEND))
				return (false);
		if (token->type == HEREDOC)
			if (!handle_heredoc_parsing(cmd, &token, HEREDOC))
				return false;
		token = token->next;
	}
	return true;
}

void	parse_tokens(t_app *shell)
{
	t_cmd *head;
	t_cmd *cmd;
	bool iswriten;

	if (!shell)
		return ;
	head = NULL;
	cmd = NULL;
	iswriten = true;
	if (shell->is_valid_syntax)
	{
		cmd = create_new_cmd();
		if (!cmd)
			exit_with_error(shell, 1, MALLOC_FAIL);
		if (!handle_token_parsing(shell, &head, &cmd, &iswriten))
			exit_with_error(shell, 1, MALLOC_FAIL);
		add_cmd_back(&head, cmd);
		shell->cmd = head;
	}
}
