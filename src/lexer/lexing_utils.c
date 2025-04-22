/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibondarc <ibondarc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 15:40:12 by ibondarc          #+#    #+#             */
/*   Updated: 2025/02/17 15:40:12 by ibondarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	skip_spases(char *input, int *i)
{
	while (input[*i] == 32 || input[*i] == 9)
		(*i)++;
}

char	*ft_devide_string(char *input, int *i, char delim, bool *is_open_q)
{
	char	*res;
	int		j;
	int		len;

	if (!input)
		return (NULL);
	len = 0;
	while (input[len] != delim)
	{
		len++;
		if (input[len] == '\"')
			*is_open_q = !(*is_open_q);
	}
	res = ft_calloc((len + 1), sizeof(char));
	j = 0;
	while (j < len)
	{
		res[j] = input[j];
		j++;
		(*i)++;
	}
	return (res);
}

bool	define_valid_string(char *input)
{
	int		i;
	bool	sing_quote;
	bool	doub_quote;

	i = 0;
	sing_quote = true;
	doub_quote = true;
	while (input[i])
	{
		if (input[i] == '\"')
		{
			if (sing_quote)
				doub_quote = !doub_quote;
		}
		else if (input[i] == '\'')
		{
			if (doub_quote)
				sing_quote = !sing_quote;
		}
		i++;
	}
	return (sing_quote && doub_quote);
}
