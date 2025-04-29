/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_list_memory.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibondarc <ibondarc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 12:19:35 by ibondarc          #+#    #+#             */
/*   Updated: 2025/02/05 12:19:35 by ibondarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_redir_list(t_redir **redir)
{
	t_redir	*temp;

	if (!redir)
		return ;
	while (*redir != NULL)
	{
		temp = (*redir)->next;
		if ((*redir)->value)
			free((*redir)->value);
		if ((*redir)->stop_word)
			free((*redir)->stop_word);
		free(*redir);
		*redir = temp;
	}
	free(*redir);
	*redir = NULL;
}

void	free_cmd_list(t_cmd **cmd)
{
	t_cmd	*temp;

	if (!cmd)
		return ;
	while (*cmd != NULL)
	{
		temp = (*cmd)->next;
		if ((*cmd)->cmd)
		{
			free((*cmd)->cmd);
			(*cmd)->cmd = NULL;
		}
		if ((*cmd)->args)
		{
			free_2d_array((*cmd)->args);
			(*cmd)->args = NULL;
		}
		close_all_redirs_fds((*cmd)->redirs);
		close_file_descriptors(*cmd);
		free_redir_list(&(*cmd)->redirs);
		free(*cmd);
		*cmd = temp;
	}
	free(*cmd);
	*cmd = NULL;
}

void	free_token_list(t_token **tokens)
{
	t_token	*temp;

	if (!(*tokens))
		return ;
	while (*tokens != NULL)
	{
		temp = (*tokens)->next;
		if ((*tokens)->value)
		{
			free((*tokens)->value);
			(*tokens)->value = NULL;
		}
		free(*tokens);
		*tokens = temp;
	}
	free(*tokens);
	*tokens = NULL;
}

void	free_envp_list(t_envp **envp)
{
	t_envp	*temp;

	if (!envp)
		return ;
	while (*envp != NULL)
	{
		temp = (*envp)->next;
		free((*envp)->name);
		free((*envp)->envp);
		free(*envp);
		*envp = temp;
	}
	free(*envp);
	*envp = NULL;
}

void	free_list(t_app *shell)
{
	if (!shell)
		return ;
	if (shell->env_var)
	{
		free_2d_array(shell->env_var);
		shell->env_var = NULL;
	}
	free_prompt(shell);
	free_token_list(&shell->tokens);
	free_cmd_list(&shell->cmd);
}
