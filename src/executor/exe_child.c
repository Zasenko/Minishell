/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_child.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzasenko <dzasenko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 16:15:59 by dzasenko          #+#    #+#             */
/*   Updated: 2025/04/30 10:55:42 by dzasenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"


void handle_execve_error(t_app *shell, t_cmd *cmd)
{
    struct stat buffer;

	if (find_path(shell) && !*find_path(shell))
		{
			ft_putstr_fd(cmd->args[0], 2);
            ft_putstr_fd(": No such file or directory\n", 2);
			exit_child(shell, 127, NULL);

		}
		if (!find_path(shell) && !cmd->is_valid_cmd )
        {
            ft_putstr_fd(cmd->args[0], 2);
            ft_putstr_fd(": Permission denied\n", 2);
            exit_child(shell, 126, NULL);

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

void	execve_in_child(t_app *shell, t_cmd *cmd)
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

void	child_process(t_app *shell, t_cmd *cmd)
{
	int exit_status;

	handle_child_signal();
	redirects_in_child(shell, cmd);
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
