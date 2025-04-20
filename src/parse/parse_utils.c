/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 16:51:46 by marvin            #+#    #+#             */
/*   Updated: 2025/02/23 16:51:46 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	is_valid_brackets(char *str, char c)
{
	if (!ft_strchr(str, c, false))
		return (false);
	return (true);
}

char	*extract_subcommand(const char *str)
{
	char *result;
	int start;
	int length;

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

char	*extract_word_from_quotes(char *input)
{
	int i = 0, j = 0;
	int len;
	char *res;
	char quote = 0;

	if (!input)
		return (NULL);
	len = ft_strlen(input);
	res = (char *)malloc((len + 1) * sizeof(char));
	if (!res)
		return (NULL);
	while (input[i])
	{
		if (!quote && (input[i] == '\'' || input[i] == '\"'))
			quote = input[i];
		else if (quote && input[i] == quote)
			quote = 0;
		else
			res[j++] = input[i];
		i++;
	}
	res[j] = '\0';
	return (res);
}
