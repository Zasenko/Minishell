/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibondarc <ibondarc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 10:48:14 by ibondarc          #+#    #+#             */
/*   Updated: 2025/01/30 13:45:10 by ibondarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/ft_printf.h"

int	ft_printf(const char *format, ...)
{
	va_list	args;
	int		total_len;

	if (!format)
		return (-1);
	va_start(args, format);
	total_len = 0;
	while (*format)
	{
		if (*format == '%')
		{
			format++;
			if (*format == ' ' || *format == '\0')
				return (-1);
			total_len += ft_handle_args(args, *format);
		}
		else
			total_len += ft_print_char(*format);
		format++;
	}
	va_end(args);
	return (total_len);
}
