/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibondarc <ibondarc@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 14:50:02 by ibondarc          #+#    #+#             */
/*   Updated: 2025/02/14 14:50:02 by ibondarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*find_path(t_app *shell)
{
	t_envp	*envp;

	envp = shell->envp;
	while (envp != NULL)
	{
		if (ft_strncmp(envp->name, "PATH", 4) == 0)
		{
			return (envp->envp);
		}
		envp = envp->next;
	}
	return (NULL);
}

char	*extract_full_path(char **paths, t_cmd *err, char *cmd)
{
	int		i;
	char	*full_path;
	char	*temp_path;

	i = 0;
	while (paths[i])
	{
		temp_path = ft_strjoin(paths[i++], "/");
		if (!temp_path)
			return (NULL);
		full_path = ft_strjoin(temp_path, cmd);
		free(temp_path);
		if (!full_path)
			return (NULL);
		if (access_checking(full_path))
			break ;
		free(full_path);
		full_path = NULL;
	}
	if (!full_path)
	{
		err->is_valid_cmd = false;
		return (ft_strdup(""));
	}
	return (full_path);
}

char	*handle_cmd_without_env(t_app *shell, t_cmd *cmd, char *value)
{
	char	*full_path;
	char	*temp_path;

	temp_path = ft_strjoin(shell->pwd, "/");
	if (!temp_path)
		return (NULL);
	full_path = ft_strjoin(temp_path, value);
	free(temp_path);
	if (!full_path)
		return (NULL);
	if (!access_checking(full_path))
	{
		cmd->is_valid_cmd = false;
	}
	return (full_path);
}

char	*handle_cmd_path(t_app *shell, t_cmd *cmd, char *value)
{
	char	*env_path;
	char	**paths;
	char	*result;

	env_path = NULL;
	env_path = find_path(shell);
	if (env_path && *env_path)
	{
		paths = ft_split(env_path, ':');
		if (!paths)
			return (NULL);
		result = extract_full_path(paths, cmd, value);
		free_2d_array(paths);
		if (!result)
			return (NULL);
	}
	else
	{
		result = handle_cmd_without_env(shell, cmd, value);
		if (!result)
			return (NULL);
	}
	return (result);
}

char	*parse_command(t_app *shell, t_cmd *cmd, char *value)
{
	char	*result;

	if (ft_strchr(value, '/', false) || value[0] == '\0')
	{
		result = ft_strdup(value);
		if (!result)
			return (NULL);
	}
	else
	{
		if (is_builtin_func(value) == true)
		{
			result = ft_strdup(value);
			if (!result)
				return (NULL);
		}
		else
		{
			result = handle_cmd_path(shell, cmd, value);
			if (!result)
				return (NULL);
		}
	}
	return (result);
}
