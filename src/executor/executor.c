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

int	close_all_redirs_fds2(t_redir *redir)
{
	t_redir	*temp;

	temp = redir;
	if (!temp)
		return (0);
	while (temp != NULL)
	{
		if (temp->fd != -1)
		{
			close(temp->fd);
		}
		temp = temp->next;
	}
	return (1);
}

void free_cmd_list2(t_cmd **cmd)
{
    t_cmd *temp;

    if (!cmd)
        return ;
    while (*cmd != NULL)
    {
        temp = (*cmd)->next;
        if ((*cmd)->args)
        {
            free_2d_array((*cmd)->args);
            (*cmd)->args = NULL;
        }
        close_all_redirs_fds2((*cmd)->redirs);
        free(*cmd);
        *cmd = temp;
    }
    free(*cmd);
    *cmd = NULL;
}

void free_list2(t_app *shell)
{
    if (!shell)
        return ;
    // if (shell->path)
    //     free_2d_array(shell->path);
    if (shell->env_var)
    {
        free_2d_array(shell->env_var);
        shell->env_var = NULL;
    }
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
    free_cmd_list2(&shell->cmd);
    free_token_list(&shell->tokens); 
}

void child_heredock(t_app *shell, t_redir *redir, int fd)
{
	signal(SIGINT, SIG_DFL);
    // signal(SIGQUIT, SIG_DFL);

	char *input = readline("> ");

	if (!input)
	{
		if (input)
			free(input);

		free_list2(shell);
		close(redir->fd);
		close(fd);
		exit(3);
	}
	if (!ft_strncmp(redir->stop_word, input, ft_strlen(input)))
	{
		free(input);
		free_list2(shell);
		close(redir->fd);
		close(fd);
		exit(55);
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
		free_list2(shell);
		close(redir->fd);
		close(fd);
		exit(EXIT_FAILURE);
			//todo
	}
	write(redir->fd, temp, ft_strlen(temp));
	free(temp);
	free_list2(shell);
	close(redir->fd);
	exit(EXIT_SUCCESS);
}

void	ft_putfullstr_fd(char *s, int fd)
{
	if (!s || !(fd >= 0))
		return ;
	int len = ft_strlen(s);
	write(fd, s, len);
}

int	close_all_redirs_fds(t_redir *redir)
{
	t_redir	*temp;

	temp = redir;
	if (!temp)
		return (0);
	while (temp != NULL)
	{
		if (temp->fd != -1)
		{
			close(temp->fd);
		}
		if (temp->type == HEREDOC)
		{
			unlink(temp->value);
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
		close_all_redirs_fds(temp->redirs);
		temp = temp->next;
	}
	return (1);
}

int	redirect(t_app *shell, t_cmd *cmd, int prev_pipe, int pipe_fd[2])
{
	(void) shell;
	if (prev_pipe != -1)
	{
		dup2(prev_pipe, 0);
		close(prev_pipe);
	}

	if (cmd->next != NULL)
	{
		dup2(pipe_fd[1], 1);
	}
	
	t_redir *redir = cmd->redirs;
	while (redir)
	{
		if (redir->type == REDIR_IN && redir->fd != -1)
		{
			dup2(redir->fd, 0);
			close(redir->fd);
		} 
		else if (redir->type == HEREDOC && redir->fd != -1)
		{
			dup2(redir->fd, 0);
			close(redir->fd);
		} else if (redir->type == REDIR_OUT && redir->fd != -1)
		{
			dup2(redir->fd, 1);
			close(redir->fd);
		} else if (redir->type == APPEND && redir->fd != -1)
		{
			dup2(redir->fd, 1);
			close(redir->fd);
		} else {
			free_list(shell);
			exit(EXIT_FAILURE);
		}
		redir = redir->next;
	}
	if (pipe_fd[0] != -1)
		close(pipe_fd[0]);
	if (pipe_fd[1] != -1)
		close(pipe_fd[1]);
	return (1);
}

int handle_execve_error(t_cmd *cmd)
{
    struct stat buffer;

	if (!cmd->is_valid_cmd || cmd->cmd[0] == '\0' || 
        !ft_strcmp(cmd->args[0], ".") || !ft_strcmp(cmd->args[0], ".."))
    {
        char *error_msg = ft_strjoin(cmd->args[0], ": command not found\n");
		if (!error_msg)
			return 1;
		ft_putfullstr_fd(error_msg, 2);
		free(error_msg);
		return (127);
    }
    if (stat(cmd->cmd, &buffer) == 0)
    {
        if (S_ISDIR(buffer.st_mode))
        {
			char *error_msg = ft_strjoin(cmd->args[0], ": Is a directory\n");
			if (!error_msg)
				return 1;
			ft_putfullstr_fd(error_msg, 2);
			free(error_msg);
            return (126);
        }
        else if (access(cmd->cmd, X_OK) == -1)
        {
			char *error_msg = ft_strjoin(cmd->args[0], ": Permission denied\n");
			if (!error_msg)
				return 1;
			ft_putfullstr_fd(error_msg, 2);
			free(error_msg);
			return (126);
        }
    }
    else
    {
        if (errno == ENOENT || errno == ENOTDIR)
        {
			char *error_msg = ft_strjoin(cmd->args[0], ": No such file or directory\n");
			if (!error_msg)
				return 1;
			ft_putfullstr_fd(error_msg, 2);
			free(error_msg);
			return (127);
        }
    }
	char *error_msg = ft_strjoin(cmd->args[0], ": command not found\n");
	if (!error_msg)
		return 1;
	ft_putfullstr_fd(error_msg, 2);
	free(error_msg);
    return (127);
}

void	child_process(t_app *shell, t_cmd *cmd, int prev_pipe, int pipe_fd[2])
{
	int exit_status;

	handle_child_signal();
	redirect(shell, cmd, prev_pipe, pipe_fd);
	close_all_cmnds_fds(shell->cmd);
	if (is_builtin_func(cmd->args[0]))
	{
		exit_status = exec_buildin(cmd, shell, true, 1);
		free_list(shell);
		exit(exit_status);
	}
	else
	{
		execve(cmd->cmd, cmd->args, shell->env_var);
		exit_status = handle_execve_error(cmd);
		free_list(shell);
		exit(exit_status);
	}
}

int	ft_execute_command(t_app *shell, t_cmd *cmd, int *prev_pipe)
{
	int	pipe_fd[2];

	pipe_fd[0] = -1;
	pipe_fd[1] = -1;
	if (cmd->next != NULL)
	{
		if (pipe(pipe_fd) != 0)
		{
			// check
			perror("pipe");
			shell->last_exit_code = errno;
			return (EXIT_FAILURE); // todo? break and waitpid?
		}
	}
	// signal(SIGINT, SIG_IGN);
	cmd->pid = fork();
	if (cmd->pid < 0)
	{
		perror("fork");
		shell->last_exit_code = errno;
		return (EXIT_FAILURE);
	}
	// handle_child_signal();

	if (cmd->pid == 0)
	{
		child_process(shell, cmd, *prev_pipe, pipe_fd);
	}
	// handle_signal();
	// printf("pid id: %d\n", cmd->pid);
	close_all_redirs_fds(cmd->redirs);
	if (*prev_pipe != -1)
		close(*prev_pipe);
	if (pipe_fd[1] != -1)
		close(pipe_fd[1]);
	*prev_pipe = pipe_fd[0];
	return (1);
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
		if (WTERMSIG(status) == SIGQUIT)
			*print_sig_error = 1;
		t_cmd *temp_cmd = shell->cmd;
		while (temp_cmd)
		{
			if (kill(temp_cmd->pid, 0) == 0)
				kill(temp_cmd->pid, SIGINT);
			temp_cmd = temp_cmd->next;
		}
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
		if (shell->last_exit_code == 131)
		{
			printf("Quit (core dumped)\n");
		}
	}
	return (1);
}

void print_fd_err(char *val, char *err_msg)
{
	if (!val || !err_msg)
		return;
	ft_putstr_fd(val, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(err_msg, 2);
	ft_putstr_fd("\n", 2);
}

int	ft_execute(t_app *shell)
{
	t_cmd	*cmd;
	int		cmd_count;
	int		prev_pipe;

	
	cmd_count = cmd_len(shell->cmd);
	prev_pipe = -1;
	if (!cmd_count || !shell->is_valid_syntax)
		return (0);

	//HEREDOCs
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
				redir->value = ft_strjoin("HEREDOCK_", heredoc_num);
				if (!redir->value)
				{
					free(heredoc_num);
					//todo error
				}
				free(heredoc_num);
				
				//check if file exist!!!
				redir->fd = open(redir->value, O_RDWR | O_CREAT | O_APPEND, 0644);
				if (redir->fd < 0)
				{
					print_fd_err(redir->value, strerror(errno));
					shell->last_exit_code = 1;
					break;
				}

				handle_heredoc_signal();
				while (1)
				{
					
					int signal_code = signal_last_code();	
					// printf("\n --------START WITH: %d -------- \n", signal_code);
					if (signal_code == SIGQUIT)
					{
						// printf("--- START SIGQUIT --- \n");
						ft_putstr_fd("bash: warning: here-document delimited by end-of-file (wanted `", 2);
						ft_putstr_fd(redir->stop_word, 2);	
						ft_putstr_fd("')\n", 2);
						break;
					}
					else if (signal_code == SIGINT)
					{
						// printf("--- START SIGINT --- \n");
						shell->last_exit_code = 128 + WTERMSIG(signal_code);
						handle_signal();
						return 0;
					}
					char *input = readline("> ");
					if (!input)
					{
						// printf("-- NO INPUT: %d --\n", signal_last_code());
						if (signal_last_code() == 2)
						{
							int df_0 = open("/dev/tty", O_RDONLY);
							if (df_0 == 0)
							{
								// printf("open new fd 0\n");
							}
							if (df_0 < 0)
							{
								// printf("open new fd 0 - ERROR\n");
							}
							return 0;
						}
						break;
					}
					
					if (!ft_strcmp(redir->stop_word, input))
					{
						// printf("-- STOP WORD found: %s, input: %s--\n", redir->stop_word, input);
						break;
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
						//todo
					}
					write(redir->fd, temp, ft_strlen(temp));
				}
				handle_signal();
				close(redir->fd);
				redir->fd = open(redir->value, O_RDONLY, 0644);
				if (redir->fd < 0)
				{
					print_fd_err(redir->value, strerror(errno));
					shell->last_exit_code = 1;
				}
				shell->heredock_num++;
			}
			redir = redir->next;
		}

		cmd = cmd->next;
	}


	
	//REDIR
	cmd = shell->cmd;
	while (cmd != NULL)
	{

		t_redir *redir = cmd->redirs;
		while (redir)
		{
			if (redir->type == REDIR_IN)
			{
				int fd_in = open(redir->value, O_RDONLY);
				if (fd_in < 0)
				{
					print_fd_err(redir->value, strerror(errno));
					shell->last_exit_code = 1;
					break;
				}
				else
				{
					redir->fd = fd_in;
				}
			}
			if (redir->type == REDIR_OUT)
			{
				int fd_out = open(redir->value, O_WRONLY | O_CREAT |  O_TRUNC, 0644);
				if (fd_out < 0)
				{
					print_fd_err(redir->value, strerror(errno));
					shell->last_exit_code = 1;
					break;
				}
				else
				{
					redir->fd = fd_out;
				}
			}
			if (redir->type == APPEND)
			{
				int fd_append = open(redir->value, O_WRONLY | O_CREAT | O_APPEND, 0644);
				if (fd_append < 0)
				{
					print_fd_err(redir->value, strerror(errno));
					shell->last_exit_code = 1;
					break;

				}
				else
				{
					redir->fd = fd_append;
				}
			}
			redir = redir->next;
		}
		cmd = cmd->next;
	}
	
	// EXE
	cmd = shell->cmd;
	if (!cmd || !cmd->args)
	{
		return 0;
	}
	if (cmd->next == NULL && is_builtin_func(cmd->args[0]))
	{

		int dup_0 = -1;
		int dup_1 = -1;

		dup_0 = dup(0);
		dup_1 = dup(1);

		// printf("Redirection 0 - 1: %d | %d\n", dup_0, dup_1);

		// ft_putstr_fd("no child\n", 1);
		//todo double code
		t_redir *redir = cmd->redirs;
		while (redir)
		{
			// printf("Redirection type: %d, fd: %d\n", redir->type, redir->fd);

			if (redir->type == REDIR_IN && redir->fd != -1)
			{
				dup2(redir->fd, dup_0);
				close(redir->fd);
			} 
			else if (redir->type == HEREDOC && redir->fd != -1)
			{
				dup2(redir->fd, dup_0);
				close(redir->fd);
			} 
			else if (redir->type == REDIR_OUT && redir->fd != -1)
			{
				dup2(redir->fd, dup_1);
				close(redir->fd);
			} 
			else if (redir->type == APPEND && redir->fd != -1)
			{
				dup2(redir->fd, dup_1);
				close(redir->fd);
			} else {
				free_list(shell);
				exit(EXIT_FAILURE);
			}
			redir = redir->next;
		}

		shell->last_exit_code = exec_buildin(cmd, shell, false, dup_1);
		close(dup_0);
		close(dup_1);
	}
	else
	{
		handle_child_signal();
		while (cmd != NULL)
		{
			ft_execute_command(shell, cmd, &prev_pipe);
			cmd = cmd->next;
		}
	}
	ft_wait_children(shell); // todo return 0 or 1
	handle_signal();
	if (prev_pipe != -1)
		close(prev_pipe);
	close_all_cmnds_fds(shell->cmd);
	return (1);
}