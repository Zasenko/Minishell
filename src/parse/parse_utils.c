/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibondarc <ibondarc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 16:51:46 by ibondarc          #+#    #+#             */
/*   Updated: 2025/02/23 16:51:46 by ibondarc         ###   ########.fr       */
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

char	*extract_subcommand(const char *str)
{
	int		start;
	int		length;
	char	*result;

	start = 0;
	while (str[start] && str[start] != '(')
		start++;
	start++;
	length = ft_strlen(str) - start;
	result = ft_substr(str, start, length - 1);
	if (!result)
		return (NULL);
	return (result);
}

bool	is_there_quote(char *str)
{
	while (*str)
	{
		if (*str == '\'' || *str == '\"')
			return (true);
		str++;
	}
	return (false);
}

void	handle_quotes_extraction(char *dest, char *input)
{
	int		j;
	int		i;
	char	quote;

	j = 0;
	i = 0;
	quote = 0;
	while (input[i])
	{
		if (!quote && (input[i] == '\'' || input[i] == '\"'))
			quote = input[i];
		else if (quote && input[i] == quote)
			quote = 0;
		else
			dest[j++] = input[i];
		i++;
	}
	dest[j] = '\0';
}

char	*extract_word_from_quotes(char *input)
{
	int		len;
	char	*res;

	if (!input)
		return (NULL);
	len = ft_strlen(input);
	res = (char *)malloc((len + 1) * sizeof(char));
	if (!res)
		return (NULL);
	handle_quotes_extraction(res, input);
	return (res);
}
