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




#include <libgen.h>

int	redirect_in_child(t_app *shell, t_cmd *cmd)
{
	(void) shell;
	if (shell->prev_pipe != -1)
	{
		dup2(shell->prev_pipe, 0);
		close(shell->prev_pipe);
	}
	if (cmd->next != NULL)
	{
		dup2(cmd->pipe_fd[1], 1);
		close_file_descriptors(cmd);
	}
	t_redir *redir = cmd->redirs;
	while (redir)
	{
		if (redir->type == REDIR_IN || redir->type == HEREDOC)
		{
			redir->fd = open(redir->value, O_RDONLY, 0644);
			if (redir->fd < 0)
			{
				print_fd_err(redir->value, strerror(errno));
				exit_child(shell, 1, NULL);
			}
			dup2(redir->fd, 0);
			close(redir->fd);
		}
		else if (redir->type == REDIR_OUT)
		{
			redir->fd = open(redir->value, O_WRONLY | O_CREAT |  O_TRUNC, 0644);
			if (redir->fd < 0)
			{
				print_fd_err(redir->value, strerror(errno));
				exit_child(shell, 1, NULL);
			}
			dup2(redir->fd, 1);
			close(redir->fd);
		}
		else if (redir->type == APPEND)
		{
			redir->fd = open(redir->value, O_WRONLY | O_CREAT | O_APPEND, 0644);
			if (redir->fd < 0)
			{
				print_fd_err(redir->value, strerror(errno));
				exit_child(shell, 1, NULL);
			}
			dup2(redir->fd, 1);
			close(redir->fd);
		}
		redir = redir->next;
	}
	close_file_descriptors(cmd);
	return (1);
}

void handle_execve_error(t_app *shell, t_cmd *cmd)
{
    struct stat buffer;

	if (find_path(shell) && !*find_path(shell))
		{
			ft_putstr_fd(cmd->args[0], 2);
            ft_putstr_fd(": No such file or directory\n", 2);
			// free_list(shell);
			// free_envp_list(&shell->envp);
            // exit(127);
			exit_child(shell, 127, NULL);

		}
		if (!find_path(shell) && !cmd->is_valid_cmd )
        {
            ft_putstr_fd(cmd->args[0], 2);
            ft_putstr_fd(": Permission denied\n", 2);
			free_list(shell);
			free_envp_list(&shell->envp);
            exit(126);
			// exit_child(shell, 126, NULL);

        }

	else if (find_path(shell) == NULL)
	{
		ft_putstr_fd(cmd->args[0], 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		exit_child(shell, 127, NULL);
	}

	else if (!cmd->is_valid_cmd || cmd->cmd[0] == '\0' || 
        !ft_strcmp(cmd->args[0], ".") || !ft_strcmp(cmd->args[0], ".."))
    {
        ft_putstr_fd(cmd->args[0], 2);
        ft_putstr_fd(": command not found\n", 2);
        exit_child(shell, 127, NULL);
    }
    else if (stat(cmd->cmd, &buffer) == 0)
    {
        if (S_ISDIR(buffer.st_mode))
        {
            ft_putstr_fd(cmd->args[0], 2);
            ft_putstr_fd(": Is a directory\n", 2);
            exit_child(shell, 126, NULL);
        }
        else if ( access(cmd->cmd, X_OK) == -1)
        {
            ft_putstr_fd(cmd->args[0], 2);
            ft_putstr_fd(": Permission denied\n", 2);
            exit_child(shell, 126, NULL);
        }
    }
    else
    {
        if (errno == ENOENT || errno == ENOTDIR)
        {
            ft_putstr_fd(cmd->args[0], 2);
            ft_putstr_fd(": No such file or directory\n", 2);
			exit_child(shell, 127, NULL);
        }
    }
    ft_putstr_fd(cmd->args[0], 2);
    ft_putstr_fd(": command not found\n", 2);
	exit_child(shell, 127, NULL);
}

void	child_process(t_app *shell, t_cmd *cmd)
{

	int exit_status;

	handle_child_signal();
	redirect_in_child(shell, cmd);
	if (!cmd->args)
		exit_child(shell, 0, NULL);
	if (is_builtin_func(cmd->args[0]))
	{
		signal(SIGPIPE, SIG_IGN);
		exit_status = exec_buildin(cmd, shell, true, 1);
		exit_child(shell, exit_status, NULL);
	}
	else
	{
		if (ft_strstr(cmd->args[0], "/minishell"))
		{
			t_envp *node = find_envp_node(shell->envp, "SHLVL");
			if (node && node->envp)
			{
				int level = ft_atoi(node->envp);
				level++;
				char *new_lvl = ft_itoa(level);
				if (!new_lvl)
				{
					//todo;
				}
				free(node->envp);
				node->envp = new_lvl;

				char **new_2d_env = copy_into_2d_arr(shell->envp);
				if (!new_2d_env)
				{
					//todo;
				}
				if (shell->env_var)
				{
					free_2d_array(shell->env_var);
					shell->env_var = NULL;
					shell->env_var = new_2d_env;
				}
			}
		}
		if (cmd->cmd == NULL)
			execve(cmd->args[0], cmd->args, shell->env_var);
		else
			execve(cmd->cmd, cmd->args, shell->env_var);
		handle_execve_error(shell, cmd);
	}
}

int	ft_execute_command(t_app *shell, t_cmd *cmd)
{
	if (cmd->next != NULL)
	{
		if (pipe(cmd->pipe_fd) != 0)
		{
			// check
			perror("pipe");
			shell->last_exit_code = errno;
			return (EXIT_FAILURE); // todo? break and waitpid?
		}
	}
	cmd->pid = fork();
	if (cmd->pid < 0)
	{
		perror("fork");
		shell->last_exit_code = errno;
		return (EXIT_FAILURE);
	}
	if (cmd->pid == 0)
		child_process(shell, cmd);
	if (shell->prev_pipe != -1)
		close(shell->prev_pipe);
	if (cmd->pipe_fd[1] != -1)
		close(cmd->pipe_fd[1]);
	shell->prev_pipe = cmd->pipe_fd[0];
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
	if (WIFEXITED(status)) //exit (1)
	{
		shell->last_exit_code = WEXITSTATUS(status);
		return (SUCCESS);
	}
	else if (WIFSIGNALED(status))
	{
		// printf("--- command: %s, exit status %d\n", cmd->cmd,  128 + WTERMSIG(status));
		shell->last_exit_code = 128 + WTERMSIG(status);
		if (WTERMSIG(status) == SIGINT)
		{
			*print_sig_error = 2;
			// t_cmd *temp_cmd = shell->cmd->next;
			// while (temp_cmd)
			// {
			// 	if (kill(temp_cmd->pid, 0) == 0)
			// 		kill(temp_cmd->pid, SIGUSR1);
			// 	temp_cmd = temp_cmd->next;
			// }
		}
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
		{
			printf("\n");
		}
		if (print_sig_error == 3 && shell->last_exit_code == 131)
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

	cmd_count = cmd_len(shell->cmd);
	if (!cmd_count || !shell->is_valid_syntax)
		return (0);
	
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

		int dup_0 = -1;
		int dup_1 = -1;

		dup_0 = dup(0);
		dup_1 = dup(1);

		t_redir *redir = cmd->redirs;
		while (redir)
		{
			if (redir->type == REDIR_IN || redir->type == HEREDOC)
			{
				redir->fd = open(redir->value, O_RDONLY);
				if (redir->fd < 0)
				{
					print_fd_err(redir->value, strerror(errno));
					shell->last_exit_code = 1;
					if (dup_0 >= 0)
						close(dup_0);
					if (dup_1 >= 0)
						close(dup_1);
					return 1;
				}
				dup2(redir->fd, dup_0);
				close(redir->fd);
			} 
			else if (redir->type == REDIR_OUT)
			{
				redir->fd = open(redir->value, O_WRONLY | O_CREAT |  O_TRUNC, 0644);
				if (redir->fd < 0)
				{
					if (dup_0 >= 0)
						close(dup_0);
					if (dup_1 >= 0)
						close(dup_1);
					print_fd_err(redir->value, strerror(errno));
					return (1);
				}
				dup2(redir->fd, dup_1);
				close(redir->fd);
			} 
			else if (redir->type == APPEND)
			{
				redir->fd = open(redir->value, O_WRONLY | O_CREAT | O_APPEND, 0644);
				if (redir->fd < 0)
				{
					if (dup_0 >= 0)
						close(dup_0);
					if (dup_1 >= 0)
						close(dup_1);
					print_fd_err(redir->value, strerror(errno));
					return (1);
				}
				dup2(redir->fd, dup_1);
				close(redir->fd);
			}
			redir = redir->next;
		}

		shell->last_exit_code = exec_buildin(cmd, shell, false, dup_1);
		close(dup_0);
		close(dup_1);
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
	}
	ft_wait_children(shell);
	handle_signal_main();
	if (shell->prev_pipe != -1)
		close(shell->prev_pipe);
	// close_all_redirs_fds(cmd->redirs);
	// close_all_cmnds_fds(shell->cmd);
	return (1);
}