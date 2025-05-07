/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzasenko <dzasenko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 13:44:32 by dzasenko          #+#    #+#             */
/*   Updated: 2025/05/07 11:08:55 by dzasenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	heredoc_non_expand(char *input, t_heredoc *hd)
{
	char	*substr;

	substr = ft_substr(input, hd->start, hd->j - hd->start);
	if (!substr)
		return (0);
	hd->temp = ft_strjoin(hd->dest, substr);
	free(hd->dest);
	hd->dest = NULL;
	free(substr);
	if (!hd->temp)
		return (0);
	hd->dest = hd->temp;
	return (1);
}

int	heredoc_expand(char *input, t_heredoc *hd, t_app *shell)
{
	char	*expanded;

	expanded = expand_words(shell, input, &hd->j);
	if (!expanded)
		return (0);
	hd->temp = ft_strjoin(hd->dest, expanded);
	free(hd->dest);
	hd->dest = NULL;
	free(expanded);
	if (!hd->temp)
		return (0);
	hd->dest = hd->temp;
	return (1);
}

char	*expand_heredoc_input(t_app *shell, char *input)
{
	t_heredoc	hd;

	hd.j = 0;
	hd.temp = NULL;
	hd.dest = ft_strdup("");
	if (!hd.dest)
		return (NULL);
	while (input[hd.j])
	{
		hd.start = hd.j;
		while (input[hd.j] && input[hd.j] != '$')
			hd.j++;
		if (hd.start != hd.j)
		{
			if (!heredoc_non_expand(input, &hd))
				return (free_heredoc(&hd), NULL);
		}
		if (input[hd.j] == '$')
		{
			if (!heredoc_expand(input, &hd, shell))
				return (free_heredoc(&hd), NULL);
		}
	}
	return (hd.dest);
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
