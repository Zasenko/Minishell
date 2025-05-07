/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzasenko <dzasenko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 09:49:37 by dzasenko          #+#    #+#             */
/*   Updated: 2025/05/07 11:09:56 by dzasenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_delim(char *input, t_redir *redir)
{
	if (input == NULL)
	{
		ft_putstr_fd("warning: here-document delimited by end-of-file ", 2);
		ft_putstr_fd("(wanted `", 2);
		ft_putstr_fd(redir->stop_word, 2);
		ft_putstr_fd("')\n", 2);
		return (0);
	}
	if (!ft_strncmp(redir->stop_word, input, ft_strlen(input)))
	{
		free(input);
		return (0);
	}
	return (1);
}

int	heredoc_check_signal(t_app *shell, char *input)
{
	if (last_signal_status())
	{
		if (input)
			free(input);
		shell->last_exit_code = 130;
		rl_event_hook = readline_event_hook2;
		return (0);
	}
	return (1);
}

void	heredoc_append(t_app *shell, t_redir *redir, char *input)
{
	char	*temp;

	temp = ft_strjoin(input, "\n");
	free(input);
	if (!temp)
		exit_with_error(shell, 1, MALLOC_FAIL);
	write(redir->fd, temp, ft_strlen(temp));
	free(temp);
}

int	heredoc_prompt(t_app *shell, t_redir *redir)
{
	char	*input;
	char	*dest;

	dest = NULL;
	while (1)
	{
		input = readline("> ");
		if (!heredoc_check_signal(shell, input))
			return (0);
		if (!check_delim(input, redir))
			break ;
		if (ft_strchr(input, '$', false) && redir->hd_with_quotes == false)
		{
			dest = expand_heredoc_input(shell, input);
			free(input);
			if (!dest)
				exit_with_error(shell, 1, MALLOC_FAIL);
			input = dest;
		}
		heredoc_append(shell, redir, input);
	}
	return (1);
}

int	make_heredoc(t_app *shell)
{
	t_cmd	*cmd;
	t_redir	*redir;

	cmd = shell->cmd;
	while (cmd != NULL)
	{
		redir = cmd->redirs;
		while (redir)
		{
			if (redir->type == HEREDOC)
			{
				if (create_heredoc_file(shell, redir) == 0)
					break ;
				handle_signal_heredoc();
				if (!heredoc_prompt(shell, redir))
					return (0);
				close(redir->fd);
				shell->heredock_num++;
			}
			redir = redir->next;
		}
		cmd = cmd->next;
	}
	return (1);
}
