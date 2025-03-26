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

void	child_process(t_app *shell, t_cmd *cmd, int prev_pipe, int pipe_fd[2])
{
	int exit_status;

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
		// printf("child, no build in\n");
		//todo FREE!!!!!

		execve(cmd->cmd, cmd->args, shell->env_var);

		if (cmd->cmd[0] == '\0')
		{
			ft_putstr_fd(": command not found\n", 2);
			exit(127);
		}
		else if (access(cmd->cmd, F_OK) != 0 && ft_strstr(cmd->cmd, "/"))
		{
			ft_putstr_fd(cmd->args[0], 2);
			ft_putstr_fd(": Is a directory\n", 2);
			exit(126);
		}
		else {
			if (access(cmd->cmd, F_OK) != 0)
			{
				ft_putstr_fd(cmd->args[0], 2);
				ft_putstr_fd(": command not found\n", 2);
				exit(126);
			} else {
				perror(cmd->args[0]);
				// ft_putstr_fd(strerror(errno), 2);
				exit(errno);
				// shell->last_exit_code = CMD_N_FOUND;
			}

		}	
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
	cmd->pid = fork();
	if (cmd->pid < 0)
	{
		perror("fork");
		shell->last_exit_code = errno;
		return (EXIT_FAILURE);
	}

	// child
	if (cmd->pid == 0)
		child_process(shell, cmd, *prev_pipe, pipe_fd);
	
	close_all_redirs_fds(cmd->redirs);
	if (*prev_pipe != -1)
		close(*prev_pipe);
	if (pipe_fd[1] != -1)
		close(pipe_fd[1]);
	*prev_pipe = pipe_fd[0];
	return (1);
}

int	ft_wait_child(t_cmd *cmd, t_app *shell)
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
	return (SUCCESS);
}

int ft_wait_children(t_app *shell)
{
	t_cmd	*cmd;

	cmd = shell->cmd;
	while (cmd != NULL)
	{
		if (cmd->pid != -1)
		{
			ft_wait_child(cmd, shell);
		}
		cmd = cmd->next;
	}
	return (1);
}


int	ft_execute(t_app *shell)
{
	t_cmd	*cmd;
	int		cmd_count;
	int		prev_pipe;

	cmd = shell->cmd;

	cmd_count = cmd_len(shell->cmd);
	prev_pipe = -1;
	if (!cmd_count)
		return (0);
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
					ft_putstr_fd(redir->value, 2);
					ft_putstr_fd(": No such file or directory\n", 2);
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
					ft_putstr_fd(redir->value, 2);
					ft_putstr_fd(": No such file or directory\n", 2);
					shell->last_exit_code = 0;
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
					perror(redir->value);
					// ft_putstr_fd(redir->value, 2);
					// ft_putstr_fd(": No such file or directory\n", 2);
					shell->last_exit_code = 1;
					break;

				}
				else
				{
					redir->fd = fd_append;
				}
			}
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

				redir->fd = open(redir->value, O_RDWR | O_CREAT | O_APPEND, 0644);
				if (redir->fd < 0)
				{
					ft_putstr_fd(redir->value, 2);
					ft_putstr_fd(": No such file or directory\n", 2);
					shell->last_exit_code = 1;
					break;
				}
				while (1)
				{
					char *input = readline("> ");
					if (!input)
					{
						//todo
					}
					if (!ft_strncmp(redir->stop_word, input, ft_strlen(input)))
					{
						free(input);
						break;
					}
					if (ft_strchr(input, '$', false) && redir->heredock_with_quotes == false)
					{
						int test_p = 0;
						char *test_char = expand_words(shell, input, &test_p);
						if (!test_char)
						{
							free(input);
							//todo 
						}
						free(input);
						input = test_char;			
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

				redir->fd = open(redir->value, O_RDONLY, 0644);
				if (redir->fd < 0)
				{
					//todo
				}
				shell->heredock_num++;
			}
			redir = redir->next;
		}

		cmd = cmd->next;
	}
	cmd = shell->cmd;

	// print_cmd(&shell);


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
		while (cmd != NULL)
		{
			ft_execute_command(shell, cmd, &prev_pipe);
			cmd = cmd->next;
		}
	}

	ft_wait_children(shell);

	if (prev_pipe != -1)
		close(prev_pipe);
	close_all_cmnds_fds(shell->cmd);
	return (1);
}