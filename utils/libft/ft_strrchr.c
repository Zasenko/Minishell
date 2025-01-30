/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibondarc <ibondarc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 12:31:10 by ibondarc          #+#    #+#             */
/*   Updated: 2025/01/30 12:50:12 by ibondarc         ###   ########.fr       */
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
