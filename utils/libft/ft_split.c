/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibondarc <ibondarc@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 15:08:22 by ibondarc          #+#    #+#             */
/*   Updated: 2025/05/09 14:49:45 by ibondarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

static size_t	count_words(char const *s, char c)
{
	size_t	count;
	size_t	flag;

	flag = 0;
	count = 0;
	while (*s)
	{
		if (*s != c && !flag)
		{
			flag = 1;
			count++;
		}
		else if (*s == c)
		{
			flag = 0;
		}
		s++;
	}
	return (count);
}

static char	*malloc_word(const char *start, int len)
{
	char	*word;

	word = (char *)malloc(sizeof(char) * (len + 1));
	if (!word)
		return (NULL);
	ft_strlcpy(word, start, len + 1);
	return (word);
}

static void	*free_alocated_words(char **words, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		free(words[i]);
		i++;
	}
	free(words);
	return (NULL);
}

static char	**hendle_words(char **dest, char const *s, char c)
{
	int			i;
	int			len;
	const char	*start;

	i = 0;
	while (*s)
	{
		if (*s != c)
		{
			start = s;
			len = 0;
			while (*s && *s != c)
			{
				len++;
				s++;
			}
			dest[i] = malloc_word(start, len);
			if (!dest[i])
				return (free_alocated_words(dest, i));
			i++;
		}
		else
			s++;
	}
	return (dest);
}

char	**ft_split(char const *s, char c)
{
	size_t	words;
	char	**arr;

	if (!s)
		return (NULL);
	words = count_words(s, c);
	arr = (char **)malloc(sizeof(char *) * (words + 1));
	if (!arr)
		return (NULL);
	arr[words] = NULL;
	arr = hendle_words(arr, s, c);
	return (arr);
}
