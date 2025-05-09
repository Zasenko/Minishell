/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibondarc <ibondarc@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 12:19:05 by ibondarc          #+#    #+#             */
/*   Updated: 2025/05/09 14:49:12 by ibondarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char	*d;
	unsigned char	*s;

	if (!dest && !src)
		return (dest);
	d = (unsigned char *)dest;
	s = (unsigned char *)src;
	if (d < s)
	{
		ft_memcpy(dest, src, n);
	}
	else
	{
		while (n--)
			d[n] = s[n];
	}
	return (dest);
}
