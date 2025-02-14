/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 10:21:50 by marvin            #+#    #+#             */
/*   Updated: 2025/02/13 10:21:50 by marvin           ###   ########.fr       */
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


bool parse_tokens(t_app *shell)
{
    t_token *token;
    t_cmd   *cmd;
    t_token *temp;
    char    *env_path;
    char    **paths;
    int     args_count;
    bool    isargs = true;

    if (!shell || !shell->tokens)
        return false;
    token = shell->tokens;
    shell->cmd = create_new_cmd();
    cmd = shell->cmd;
    while (token != NULL)
    {
        if (token->type == CMD)
        {
            if (ft_strchr(token->value, '/', false))
                cmd->cmd = ft_strdup(token->value);
            else
            {
                env_path = find_path(shell);
                if (env_path)
                {
                    paths = ft_split(env_path, ':');
                    if (!paths)
                        return false;
                    cmd->cmd = extract_full_path(paths, token->value);
                    free_2d_array(paths);
                    if (!cmd->cmd)
                        return (NULL);
                }
            }
            if ((!token->next || token->next->type != ARG) || token->next->type == ARG)
            {
                cmd->args = (char**)malloc(2 * sizeof(char*));
                if (!cmd->args)
                    return NULL;
                cmd->args[0] = ft_strdup(token->value);
                cmd->args[1] = NULL;
            }
        }
        if (isargs && token->type == ARG)
        {
            args_count = 0;
            temp = token;
            while (temp && temp->type == ARG )
            {
                args_count++;
                temp = temp->next;
            }
            cmd->args = (char**)malloc((args_count + 2) * sizeof(char*));
            if (!cmd->args)
                return NULL;
            args_count = 0;
            t_token *new_token = token;
            while (new_token && new_token->type == ARG)
            {
                if (args_count == 0)
                {
                    cmd->args[args_count] = ft_strdup(cmd->cmd);
                    args_count++;
                }
                cmd->args[args_count] = ft_strdup(token->value);
                new_token = new_token->next;
                args_count++;
            }
            cmd->args[args_count] = NULL;
        }
        if (token->type == PIPE)
            printf("PIPE: %s\n",token->value);
        if (token->type == REDIR_IN)
            printf("REDIR_IN: %s\n",token->value);
        if (token->type == REDIR_OUT)
            printf("REDIR_OUT: %s\n",token->value);
        if (token->type == IN_FILE)
            printf("IN_FILE: %s\n",token->value);
        if (token->type == OUT_FILE)
            printf("OUT_FILE: %s\n",token->value);
        if (token->type == QUOTE)
            printf("QUOTE: %s\n",token->value);
        token = token->next;
    }
    return true;
}