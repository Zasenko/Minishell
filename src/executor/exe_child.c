/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_child.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibondarc <ibondarc@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 16:15:59 by dzasenko          #+#    #+#             */
/*   Updated: 2025/05/06 16:49:22 by ibondarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	print_child_error(t_app *shell, t_cmd *cmd, char *massage, int exit_code)
{
	char	*error_msg;
	
	error_msg = ft_strjoin(cmd->args[0], massage);
	if (!error_msg)
		exit_child(shell, 1, NULL);
	ft_putstr_fd(error_msg, 2);
	free(error_msg);
	exit_child(shell, exit_code, NULL);
}

void	handle_execve_error(t_app *shell, t_cmd *cmd)
{
	struct stat buffer;

	if (!cmd->cmd || cmd->cmd[0] == '\0'|| 
		!ft_strcmp(cmd->args[0], ".") || !ft_strcmp(cmd->args[0], ".."))
		print_child_error(shell, cmd, CMD_NOT_FND, 127);
	if (stat(cmd->cmd, &buffer) == 0)
	{
		if (S_ISDIR(buffer.st_mode))
			print_child_error(shell, cmd, IS_DIR, 126);
		else if (access(cmd->cmd, X_OK) == -1)
			print_child_error(shell, cmd, PR, 126);
	}
	else
	{
		if (errno == ENOENT || errno == ENOTDIR)
			print_child_error(shell, cmd, NSFOD, 127);
		else
			print_child_error(shell, cmd, CMD_NOT_FND, 127);
	}
	exit(127);
}

void	change_shell_lvl(t_app *shell)
{
	t_envp	*node;
	int level;

	node = find_envp_node(shell->envp, "SHLVL");
	if (node && node->envp)
	{
		level = ft_atoi(node->envp);
		level++;
		char *new_lvl = ft_itoa(level);
		if (!new_lvl)
			exit_child(shell, 1, NULL);
		free(node->envp);
		node->envp = new_lvl;
		char **new_2d_env = copy_into_2d_arr(shell->envp);
		if (!new_2d_env)
			exit_child(shell, 1, NULL);
		if (shell->env_var)
		{
			free_2d_array(shell->env_var);
			shell->env_var = NULL;
			shell->env_var = new_2d_env;
		}
	}
}
void	execve_in_child(t_app *shell, t_cmd *cmd)
{
	if (ft_strstr(cmd->args[0], "/minishell"))
		change_shell_lvl(shell);
	if (cmd->cmd)
		execve(cmd->cmd, cmd->args, shell->env_var);
	else
		execve(cmd->args[0], cmd->args, shell->env_var);
	handle_execve_error(shell, cmd);
}


void	child_process(t_app *shell, t_cmd *cmd)
{
	int	exit_status;

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
		execve_in_child(shell, cmd);
}
