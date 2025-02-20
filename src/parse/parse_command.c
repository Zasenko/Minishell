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
    if (ft_strchr(value, '/', false))
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
                return (NULL);
            result = extract_full_path(paths, value);
            free_2d_array(paths);
			if (!result)
			{
				if (is_builtin_func(value))
            	{
					char *build_in_res = NULL;
					build_in_res = ft_strdup(value);
					if (build_in_res)
						return build_in_res;
				}
				return (NULL);
			}
        }
		else 
		{
			return (NULL);
		}
    }
    return result;
}