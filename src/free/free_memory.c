/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_memory.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibondarc <ibondarc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 21:24:31 by ibondarc          #+#    #+#             */
/*   Updated: 2025/02/03 21:24:31 by ibondarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	close_file_descriptors(t_cmd *cmd)
{
	if (cmd->pipe_fd[0] >= 0)
	{
		close(cmd->pipe_fd[0]);
		cmd->pipe_fd[0] = -1;
	}
	if (cmd->pipe_fd[1] >= 0)
	{
		close(cmd->pipe_fd[1]);
		cmd->pipe_fd[1] = -1;
	}
}

int	close_all_redirs_fds(t_redir *redir)
{
	t_redir	*temp;

	temp = redir;
	if (!temp)
		return (0);
	while (temp != NULL)
	{
		if (temp->fd > -1)
		{
			close(temp->fd);
			temp->fd = -1;
		}
		if (temp->type == HEREDOC && temp->value)
		{
			unlink(temp->value);
			free(temp->value);
			temp->value = NULL;
		}
		temp = temp->next;
	}
	return (1);
}

int	close_all_cmnds_fds(t_cmd *cmd)
{
	t_cmd	*temp;

	temp = cmd;
	if (!temp)
		return (0);
	while (temp != NULL)
	{
		close_file_descriptors(temp);
		close_all_redirs_fds(temp->redirs);
		temp = temp->next;
	}
	return (1);
}

void	free_2d_array(char **arr)
{
	int	i;

	if (!arr)
		return ;
	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		arr[i] = NULL;
		i++;
	}
	free(arr);
}

void	free_prompt(t_app *shell)
{
	if (!shell)
		return ;
	if (shell->user)
	{
		free(shell->user);
		shell->user = NULL;
	}
	if (shell->name)
	{
		free(shell->name);
		shell->name = NULL;
	}
	if (shell->pwd)
	{
		free(shell->pwd);
		shell->pwd = NULL;
	}
	if (shell->prompt)
	{
		free(shell->prompt);
		shell->prompt = NULL;
	}
}
