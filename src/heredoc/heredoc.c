/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibondarc <ibondarc@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 09:49:37 by dzasenko          #+#    #+#             */
/*   Updated: 2025/05/06 11:40:18 by ibondarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// int test(char *substr, char *dest, char *temp)
// {
// 	if (!substr)
// 		return (free(dest), NULL);
// 	temp = ft_strjoin(dest, substr);
// 	free(dest);
// 	free(substr);
// 	if (!temp)
// 		return (NULL);
// 	dest = temp;
// }

char	*expand_heredoc_input(t_app *shell, char *input)
{
	char	*dest;
	char	*temp;
	int		start;
	int		j;

	j = 0;
	dest = ft_strdup("");
	if (!dest)
		return (NULL);
	while (input[j])
	{
		start = j;
		while (input[j] && input[j] != '$')
			j++;
		if (start != j)
		{
			char *substr = ft_substr(input, start, j - start);
			if (!substr)
				return (free(dest), NULL);
			temp = ft_strjoin(dest, substr);
			free(dest);
			free(substr);
			if (!temp)
				return (NULL);
			dest = temp;
		}
		if (input[j] == '$')
		{
			char	*expanded = expand_words(shell, input, &j);
			if (!expanded)
				return (free(dest), NULL);
			temp = ft_strjoin(dest, expanded);
			free(dest);
			free(expanded);
			if (!temp)
				return (NULL);
			dest = temp;
		}
	}
	return dest;
}

void	create_heredoc_num(t_app *shell, t_redir *redir)
{
	char	*heredoc_num;

	heredoc_num = ft_itoa(shell->heredock_num);
	if (!heredoc_num)
		exit_with_error(shell, EXIT_FAILURE, MALLOC_FAIL);
	if (redir->value)
	{
		free(redir->value);
		redir->value = NULL;
	}
	redir->value = ft_strjoin(".heredoc_", heredoc_num);
	free(heredoc_num);
	if (!redir->value)
		exit_with_error(shell, EXIT_FAILURE, MALLOC_FAIL);
}

int	create_heredoc_file(t_app *shell, t_redir *redir)
{
	int	result;

	create_heredoc_num(shell, redir);
	result = access(redir->value, F_OK);
	while (!result)
	{
		shell->heredock_num++;
		create_heredoc_num(shell, redir);
		result = access(redir->value, F_OK);
	}
	redir->fd = open(redir->value, O_RDWR | O_CREAT | O_APPEND, 0644);
	if (redir->fd < 0)
	{
		print_fd_err(redir->value, strerror(errno));
		shell->last_exit_code = 1;
		return (0);
	}
	return (1);
}

int	heredoc_prompt(t_app *shell, t_redir *redir)
{
	char	*input;

	while (1)
	{
		input = readline("> ");
		if (last_signal_status())
		{
			if (input)
				free(input);
			shell->last_exit_code = 130;
			rl_event_hook = readline_event_hook2;
			return (0);   // back to prompt
		}
		if (input == NULL)
		{
			ft_putstr_fd("warning: here-document delimited by end-of-file (wanted `", 2);
			ft_putstr_fd(redir->stop_word, 2);
			ft_putstr_fd("')\n", 2);
			break;
		}
		if (!ft_strncmp(redir->stop_word, input, ft_strlen(input)))
		{
			free(input);
			break;
		}
		if (ft_strchr(input, '$', false) && redir->heredock_with_quotes == false)
		{
			char *dest = expand_heredoc_input(shell, input);
			free(input);
			if (!dest)
				exit_with_error(shell, 1, MALLOC_FAIL);
			input = dest;			
		}
		char *temp = ft_strjoin(input, "\n");
		free(input);
		if (!temp)
			exit_with_error(shell, 1, MALLOC_FAIL);
		write(redir->fd, temp, ft_strlen(temp));
		free(temp);
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
					break;
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
