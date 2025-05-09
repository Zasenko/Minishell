/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibondarc <ibondarc@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 13:40:40 by ibondarc          #+#    #+#             */
/*   Updated: 2025/02/04 12:25:19 by ibondarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

static int	get_num_len(int n)
{
	int	len;

	len = 0;
	if (n <= 0)
		len = 1;
	while (n != 0)
	{
		n /= 10;
		len++;
	}
	return (len);
}

static char	*make_str(char *dest, int n, int len)
{
	long	num;

	num = n;
	dest[len] = '\0';
	if (num == 0)
	{
		dest[0] = '0';
		return (dest);
	}
	if (num < 0)
	{
		dest[0] = '-';
		num = -num;
	}
	while (num > 0)
	{
		dest[--len] = (num % 10) + 48;
		num /= 10;
	}
	return (dest);
}

char	*ft_itoa(int n)
{
	char	*result;
	int		len;

	len = get_num_len(n);
	result = (char *)malloc(sizeof(char) * (len + 1));
	if (!result)
		return (NULL);
	make_str(result, n, len);
	return (result);
}
