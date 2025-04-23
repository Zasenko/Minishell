/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_variable.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibondarc <ibondarc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 15:41:07 by ibondarc          #+#    #+#             */
/*   Updated: 2025/02/17 15:41:07 by ibondarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*var_extractor(char *input, int *i)
{
	int		start;
	char	*result;

	start = *i;
	while (input[*i])
	{
		if (input[*i] == ' ' || input[*i] == '\"' || input[*i] == ')'
			|| input[*i] == '$' || input[*i] == '\'' || input[*i] == '/'
			|| input[*i] == 46 || input[*i] == '?')
			break ;
		(*i)++;
	}
	result = ft_substr(input, start, *i - start);
	if (!result)
		return (NULL);
	return (result);
}

char	*get_status_var(int status)
{
	char	*result;

	result = ft_itoa(status);
	if (!result)
		return (NULL);
	return (result);
}

char	*wrap_in_quotes(char *str)
{
	int		i;
	int		len;
	char	*result;

	if (!str)
		return (NULL);
	i = 0;
	len = ft_strlen(str) + 2;
	result = ft_calloc(len + 1, sizeof(char));
	if (!result)
		return (NULL);
	result[i++] = '\'';
	result[len--] = '\'';
	while (i < len)
	{
		result[i] = str[i - 1];
		i++;
	}
	return (result);
}

char	*get_env_var(t_envp *envp, char *input, int *i)
{
	char	*var;
	char	*result;
	t_envp	*var_val;

	var = var_extractor(input, i);
	if (!var)
		return (NULL);
	var_val = find_envp_node(envp, var);
	if (!var_val)
		return (free(var), NULL);
	if (var_val->envp[0] == '\"')
	{
		result = wrap_in_quotes(var_val->envp);
		if (!result)
			return (free(var), NULL);
	}
	else
	{
		result = ft_strdup(var_val->envp);
		if (!result)
			return (free(var), NULL);
	}
	free(var);
	return (result);
}

char	*expand_words(t_app *shell, char *input, int *i)
{
	char	*result;

	if (!shell || !input)
		return (NULL);
	(*i)++;
	result = NULL;
	if (input[*i] == ' ' || input[*i] == '\0' || input[*i] == '\"'
		|| input[*i] == '/' || input[*i] == '$' || input[*i] == '\t'
		|| input[*i] == '\'')
		result = ft_substr(input, *i - 1, 1);
	else if (input[*i] == '?')
	{
		(*i)++;
		result = get_status_var(shell->last_exit_code);
		if (!result)
			return (ft_strdup(""));
	}
	else if ((input[*i] >= 64 && input[*i] <= 90) || (input[*i] >= 97
			&& input[*i] <= 122))
	{
		result = get_env_var(shell->envp, input, i);
		if (!result)
			return (ft_strdup(""));
	}
	return (result);
}
