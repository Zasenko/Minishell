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
	if (!shell->tokens)
		return (false);
	while (shell->tokens != NULL)
	{
		if (shell->tokens->type == ARG && *iswriten)
			if (!parse_arguments(shell, *cmd, shell->tokens, iswriten))
				return (false);
		if (shell->tokens->type == PIPE && shell->tokens->next)
			if (!handle_pipe(head, cmd, iswriten))
				return (false);
		if (shell->tokens->type == REDIR_IN && shell->tokens->next)
			if (!handle_redir_parsing(cmd, &shell->tokens, REDIR_IN))
				return (false);
		if (shell->tokens->type == REDIR_OUT && shell->tokens->next)
			if (!handle_redir_parsing(cmd, &shell->tokens, REDIR_OUT))
				return (false);
		if (shell->tokens->type == APPEND)
			if (!handle_redir_parsing(cmd, &shell->tokens, APPEND))
				return (false);
		if (shell->tokens->type == HEREDOC)
			if (!handle_heredoc_parsing(cmd, &shell->tokens, HEREDOC))
				return false;
		shell->tokens = shell->tokens->next;
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
