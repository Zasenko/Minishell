/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibondarc <ibondarc@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 12:31:10 by ibondarc          #+#    #+#             */
/*   Updated: 2025/05/09 14:50:41 by ibondarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*re;

	re = NULL;
	while (*s)
	{
		if (*s == (char)c)
			re = (char *)s;
		s++;
	}
	if ((char)c == '\0')
		return ((char *)s);
	return (re);
}
