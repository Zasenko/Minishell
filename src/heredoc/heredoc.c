/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzasenko <dzasenko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 09:49:37 by dzasenko          #+#    #+#             */
/*   Updated: 2025/04/18 10:48:21 by dzasenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void write_heredoc_line(t_redir *redir, char *input)
{
	char *temp = ft_strjoin(input, "\n");
	free(input);
	if (!temp)
	{
		// handle allocation failure if needed
		return;
	}
	write(redir->fd, temp, ft_strlen(temp));
	free(temp);
}

char *expand_heredoc_input(t_app *shell, char *input)
{
	char *dest;
	char *temp;
	char *expanded;
    int start;

	int j = 0;
    dest = ft_strdup("");
    if (!dest)
    {
        free(input);
        exit_with_error(shell, 1, "ft_strdup error");   
    }
	while (input[j])
	{
		start = j;
		while (input[j] && input[j] != '$') j++;
		if (start != j)
		{
            char *substr = ft_substr(input, start, j - start);
            if (!substr)
            {
                free(input);
                free(dest);
                exit_with_error(shell, 1, "ft_substr error");
            }
			temp = ft_strjoin(dest, substr);
            if (!temp)
            {
                free(input);
                free(dest);
                free(substr);
                exit_with_error(shell, 1, "ft_substr error");
            }
            free(dest);
            free(substr);
			dest = temp;
		}
		if (input[j] == '$')
		{
			expanded = expand_words(shell, input, &j);
            if (!expanded)
            {
                free(input);
                free(dest);
                exit_with_error(shell, 1, "expand_words error");
            }
			temp = ft_strjoin(dest, expanded);
            if (!temp)
            {
                free(input);
                free(dest);
                free(expanded);
                exit_with_error(shell, 1, "expand_words error");
            }
			free(dest);
            free(expanded);
			dest = temp;
		}
	}
	free(input);
	return dest;
}


void heredoc_input_loop(t_app *shell, t_redir *redir)
{
	while (1)
	{
		char *input = readline("> ");
		if (last_signal_status())
		{
			if (input) free(input);
			shell->last_exit_code = 130;
			rl_event_hook = readline_event_hook2;
			return;
		}
		if (!input || !ft_strncmp(redir->stop_word, input, ft_strlen(input)))
		{
			if (!input)
			{
				ft_putstr_fd("warning: here-document delimited by end-of-file (wanted `", 2);
				ft_putstr_fd(redir->stop_word, 2);
				ft_putstr_fd("')\n", 2);
			}
			free(input);
			break;
		}
		if (ft_strchr(input, '$', false) && !redir->heredock_with_quotes)
			input = expand_heredoc_input(shell, input);
		write_heredoc_line(redir, input);
	}
}

int init_heredoc_file(t_redir *redir, t_app *shell)
{
	char *heredoc_num;
    
    heredoc_num = ft_itoa(shell->heredock_num);
	if (!heredoc_num)
		return (0);
	redir->value = ft_strjoin("HEREDOC_", heredoc_num);
	free(heredoc_num);
	if (!redir->value)
		return (0);
	redir->fd = open(redir->value, O_RDWR | O_CREAT | O_APPEND, 0644);
	if (redir->fd < 0)
	{
		print_fd_err(redir->value, strerror(errno));
		shell->last_exit_code = 1;
		return (0);
	}
	return (1);
}

void process_heredoc_in_cmd(t_app *shell, t_cmd *cmd)
{
	t_redir *redir;
    
    redir = cmd->redirs;
	while (redir)
	{
		if (redir->type == HEREDOC)
		{
			if (!init_heredoc_file(redir, shell))
				return;
			handle_signal_heredoc();
			heredoc_input_loop(shell, redir);
			close(redir->fd);
			shell->heredock_num++;
		}
		redir = redir->next;
	}
}

void create_heredoc(t_app *shell)
{
    t_cmd	*cmd;
    cmd = shell->cmd;

    while (cmd != NULL)
	{
		process_heredoc_in_cmd(shell, cmd);
		cmd = cmd->next;
	}

}

