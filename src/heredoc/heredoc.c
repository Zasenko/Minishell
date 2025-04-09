/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzasenko <dzasenko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 17:34:54 by dzasenko          #+#    #+#             */
/*   Updated: 2025/04/09 18:41:15 by dzasenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int heredoc_handler(t_app *shell, t_redir *redir)
{
	int signal_code;
	signal_code = signal_last_code();	
	char *input = readline("> ");
	if (!input)
	{
		if (signal_last_code() == 2)
		{
			int df_0 = open("/dev/tty", O_RDONLY);
			if (df_0 < 0)
			{
				return -1;
			}
            shell->last_exit_code = 130;
			return 2;
		}
		else
		{
			ft_putstr_fd("warning: here-document delimited by end-of-file (wanted `", 2);
			ft_putstr_fd(redir->stop_word, 2);
			ft_putstr_fd("')\n", 2);
			return (0);
		}
	}

	if (!ft_strcmp(redir->stop_word, input))
	{
		return (0);
	}
	if (ft_strchr(input, '$', false) && redir->heredock_with_quotes == false)
	{
		char *dest = ft_strdup("");
		char *temp;
		char *expanded;
		int j = 0;
		int start;
		while (input[j])
		{
			start = j; 
			while (input[j] && input[j] != '$')
				j++;
			if (start != j)
			{
				temp = ft_strjoin(dest, ft_substr(input, start, j - start));
				free(dest);
				dest = temp;
			}
			if (input[j] == '$')
			{
				expanded = expand_words(shell, input, &j);
				temp = ft_strjoin(dest, expanded);
				free(dest);
				dest = temp;
			}
		}
		free(input);
		input = dest;			
	}
	char *temp = ft_strjoin(input, "\n");
	free(input);
	if (!temp)
	{
		return (-1);
		//todo
	}
	write(redir->fd, temp, ft_strlen(temp));
	return (1);
}

int heredocs_maker(t_app *shell, t_redir *redir)
{
	char *heredoc_num = ft_itoa(shell->heredock_num);
	if (!heredoc_num)
	{
		// todo: error, exit
	}
	redir->value = ft_strjoin("HEREDOCK_", heredoc_num);
	if (!redir->value)
	{
		free(heredoc_num);
		// todo: error, exit
	}
	free(heredoc_num);
	
	//todo: check if file exist!!!

	redir->fd = open(redir->value, O_RDWR | O_CREAT | O_APPEND, 0644);
	if (redir->fd < 0)
	{
		print_fd_err(redir->value, strerror(errno));
		shell->last_exit_code = 1;
		return (0);
	}

	handle_heredoc_signal();
	while (1)
	{
		int heredoc_result = heredoc_handler(shell, redir);
        // printf("heredoc_handler result: %d\n", heredoc_result);
		if (heredoc_result == -1)
			return -1;
		if (heredoc_result == 0)
        {
            break;
        }
		if (heredoc_result == 2)
		{
			return (2);
		}
	}
	handle_signal();
	close(redir->fd);
	redir->fd = open(redir->value, O_RDONLY, 0644);
	if (redir->fd < 0)
	{
		//todo?
		print_fd_err(redir->value, strerror(errno));
		shell->last_exit_code = 1;
	}
	shell->heredock_num++;
	return 1;
}
//return 0; break

int heredocs_checker(t_app *shell, t_redir *redir)
{
	t_redir *temp_redir;

	temp_redir = redir;
	while (temp_redir)
	{
		if (temp_redir->type == HEREDOC)
		{
			int heredoc_result = heredocs_maker(shell, temp_redir);
            printf("heredocs_maker result: %d\n", heredoc_result);
			if (heredoc_result == 0)
				break;
			else if (heredoc_result == 2)
                return 2;
		}
		temp_redir = temp_redir->next;
	}
	return (1);
}
