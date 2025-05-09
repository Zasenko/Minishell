/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibondarc <ibondarc@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 14:48:54 by ibondarc          #+#    #+#             */
/*   Updated: 2025/05/09 14:49:33 by ibondarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

void	ft_putchar(char c, int fd)
{
	write(fd, &c, 1);
}

void	ft_putnbr_fd(int n, int fd)
{
	long	num;

	num = n;
	if (num == -2147483648)
	{
		ft_putchar('-', fd);
		ft_putchar('2', fd);
		ft_putnbr_fd(147483648, fd);
	}
	else if (num < 0)
	{
		ft_putchar('-', fd);
		num = -num;
		ft_putnbr_fd(num, fd);
	}
	else if (num > 9)
	{
		ft_putnbr_fd(num / 10, fd);
		ft_putnbr_fd(num % 10, fd);
	}
	else
	{
		ft_putchar(num + 48, fd);
	}
}
