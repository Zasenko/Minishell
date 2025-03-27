/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 14:50:02 by marvin            #+#    #+#             */
/*   Updated: 2025/02/14 14:50:02 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	access_checking(char *path)
{
	int	res;

	if (!path)
		return (0);
	if (access(path, F_OK | R_OK | X_OK) == 0)
		res = 1;
	else
		res = 0;
	return (res);
}

char *find_path(t_app *shell)
{
	t_envp	*envp;

    envp = shell->envp;
	while (envp != NULL)
	{
		if (ft_strncmp(envp->name, "PATH", 4) == 0)
		{
			return envp->envp;
		}
		envp = envp->next;
	}
	return NULL;
}

char	*extract_full_path(char **paths, char *cmd)
{
	char	*full_path;
	char	*temp_path;
	int		i;

	i = 0;
	full_path = NULL;
	temp_path = NULL;
	while (paths[i])
	{
		temp_path = ft_strjoin(paths[i], "/");
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
		i++;
	}
	return (full_path);
}

char *parse_command(t_app *shell, char *value)
{   
    char    *result;
    char    *env_path;
    char    **paths;

	env_path = NULL;
	result = NULL;
    if (ft_strchr(value, '/', false) || value[0] == '\0')
    {
        result = ft_strdup(value);
        if (!result)
            return NULL;
    }
    else
    {
		if (is_builtin_func(value) == true)
		{
			result = ft_strdup(value);
        	if (!result)
            	return NULL;
		}
		else
		{
        	env_path = find_path(shell);
        	if (env_path)
        	{
        	    paths = ft_split(env_path, ':');
        	    if (!paths)
        		{
				shell->last_exit_code = 1;
				return (NULL);
				}
        	    result = extract_full_path(paths, value);
        	    free_2d_array(paths);
				if (!result)
				{
					ft_putstr_fd(value, 2);
					ft_putstr_fd(": command not found\n", 2);
					shell->last_exit_code = 127;
					return (NULL);
				}
        	}
			else
			{
				char *temp_path = ft_strjoin(shell->pwd, "/");
				if (!temp_path)
					return (NULL);
				char *full_path = ft_strjoin(temp_path, value);
				free(temp_path);
				if (!full_path)
					return (NULL);
				if (!access_checking(full_path))
				{
					ft_putstr_fd(value, 2);
					ft_putstr_fd(": command not found\n", 2);
					shell->last_exit_code = 127;
					return NULL;
				}
				return full_path;
			}
		}
    }
    return result;
}