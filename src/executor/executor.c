/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzasenko <dzasenko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 16:49:29 by dmitryzasen       #+#    #+#             */
/*   Updated: 2025/03/07 15:52:31 by dzasenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_execute_command(t_app *shell, t_cmd *cmd)
{
	if (cmd->next != NULL)
	{
		if (pipe(shell->child_fds.pipe) != 0)
		{
			close_child_fds(shell);
			perror("pipe");
			shell->last_exit_code = errno;
			return (EXIT_FAILURE); // todo? break and waitpid?
		}
	}
	cmd->pid = fork();
	if (cmd->pid < 0)
	{
		close_child_fds(shell);
		perror("fork");
		shell->last_exit_code = errno;
		return (EXIT_FAILURE);
	}
	if (cmd->pid == 0)
		child_process(shell, cmd);
	close_fd(&shell->child_fds.pipe[1]);
	close_fd(&shell->child_fds.prev_pipe);
	shell->child_fds.prev_pipe = shell->child_fds.pipe[0];
	shell->child_fds.pipe[0] = -1;
	return (SUCCESS);
}

int	ft_wait_child(t_cmd *cmd, t_app *shell, int *print_sig_error)
{
	int		status;
	pid_t	child_pid;

	child_pid = waitpid(cmd->pid, &status, 0);
	if (child_pid == -1)
	{
		shell->last_exit_code = errno;
		return (strerror(errno), errno);
	}
	if (WIFEXITED(status))
	{
		shell->last_exit_code = WEXITSTATUS(status);
		return (SUCCESS);
	}
	else if (WIFSIGNALED(status))
	{
		shell->last_exit_code = 128 + WTERMSIG(status);
		if (WTERMSIG(status) == SIGINT)
			*print_sig_error = 2;
		else if (WTERMSIG(status) == SIGQUIT)
			*print_sig_error = 3;
		return (SUCCESS);
	}
	return (SUCCESS);
}

int ft_wait_children(t_app *shell)
{
	t_cmd	*cmd;

	cmd = shell->cmd;
	int print_sig_error = 0;
	while (cmd != NULL)
	{
		if (cmd->pid != -1)
		{
			ft_wait_child(cmd, shell, &print_sig_error); //todo return int
		}
		cmd = cmd->next;
	}

	if (print_sig_error)
	{
		if (print_sig_error == 2)
			printf("\n");
		if (print_sig_error == 3 && shell->last_exit_code == 131)
			printf("Quit (core dumped)\n");
	}
	return (1);
}

void print_fd_err(char *val, char *err_msg)
{
	char *err[4];
	char *temp;
	char *res;
	int i;

	if (!val || !err_msg)
		return;
	i = 0;
	err[0] = val;
	err[1] = ": ";
	err[2] = err_msg;
	err[3] = "\n";
	res = ft_strdup("");
	while (i < 4)
	{
		temp = ft_strjoin(res, err[i]);
		free(res);
		if (!temp)
			return ;
		res = temp;
		i++;
	}
	ft_putstr_fd(res, 2);
	free(res);
}

int	ft_execute(t_app *shell)
{
	t_cmd	*cmd;
	int		cmd_count;

	cmd_count = cmd_len(shell->cmd);
	if (!cmd_count || !shell->is_valid_syntax)
		return (EXIT_FAILURE);
	
	//HEREDOC
	cmd = shell->cmd;
	while (cmd != NULL)
	{
		t_redir *redir = cmd->redirs;
		while (redir)
		{
			if (redir->type == HEREDOC)
			{
				char *heredoc_num = ft_itoa(shell->heredock_num);
				if (!heredoc_num)
				{
					//todo error
				}
				redir->value = ft_strjoin("HEREDOC_", heredoc_num);
				if (!redir->value)
				{
					free(heredoc_num);
					//todo error
				}
				free(heredoc_num);

				redir->fd = open(redir->value, O_RDWR | O_CREAT | O_APPEND, 0644);
				if (redir->fd < 0)
				{
					print_fd_err(redir->value, strerror(errno));
					shell->last_exit_code = 1;
					break;
				}
				
				handle_signal_heredoc();
				while (1)
				{
					char *input = readline("> ");
					if (last_signal_status()) {
						if (input)
						{
							free(input);
						}
						shell->last_exit_code = 130;
						rl_event_hook = readline_event_hook2;
						return 0;   // back to prompt
					}
					if (input == NULL) { // Ctrl+D (EOF)
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
						// int test_p = 0;
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
								char *sub_str = ft_substr(input, start, j - start);
								temp = ft_strjoin(dest, sub_str);
								free(sub_str);
								free(dest);
								dest = temp;
							}
							if (input[j] == '$')
							{
								expanded = expand_words(shell, input, &j);
								temp = ft_strjoin(dest, expanded);
								free(expanded);
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
							//todo
					}
					write(redir->fd, temp, ft_strlen(temp));
					free(temp);
				}
				close(redir->fd);
				shell->heredock_num++;
			}
			redir = redir->next;
		}
		cmd = cmd->next;
	}
	
	
	//EXE
	handle_signal_main();

	cmd = shell->cmd;
	if (!cmd)
		return 0;
	if (cmd->next == NULL && cmd->args && is_builtin_func(cmd->args[0]))
	{
		if (exe_singl_buildin(shell, cmd) == EXIT_FAILURE)
			return (EXIT_FAILURE);
	}
	else
	{
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
		while (cmd != NULL)
		{
			ft_execute_command(shell, cmd);
			cmd = cmd->next;
		}
		ft_wait_children(shell);
		handle_signal_main();
	}
	return (SUCCESS);
}
