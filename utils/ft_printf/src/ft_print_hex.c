/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_hex.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibondarc <ibondarc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 15:51:38 by ibondarc          #+#    #+#             */
/*   Updated: 2025/01/30 13:44:58 by ibondarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/ft_printf.h"

int	ft_print_hex(unsigned int n, char format)
{
	int		count;
	char	*hex_digits;

	count = 0;
	if (format == 'x')
		hex_digits = "0123456789abcdef";
	else if (format == 'X')
		hex_digits = "0123456789ABCDEF";
	if (n == 0)
		count += ft_print_char('0');
	else
		count += ft_puthex((uintptr_t)n, hex_digits);
	return (count);
}
