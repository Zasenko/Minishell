/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puthex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibondarc <ibondarc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 16:04:35 by ibondarc          #+#    #+#             */
/*   Updated: 2025/01/30 13:45:12 by ibondarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/ft_printf.h"

int	ft_puthex(uintptr_t num, char *format)
{
	int	len;

	len = 0;
	if (num >= 16)
		len += ft_puthex((num / 16), format);
	len += ft_print_char(format[num % 16]);
	return (len);
}
