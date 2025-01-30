/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handle_args.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibondarc <ibondarc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 21:23:31 by igoryan           #+#    #+#             */
/*   Updated: 2025/01/30 14:36:19 by ibondarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/ft_printf.h"

int	ft_handle_args(va_list args, char format)
{
	int	count;

	count = 0;
	if (format == 'c')
		count += ft_print_char(va_arg(args, int));
	if (format == 's')
		count += ft_print_str(va_arg(args, char *));
	if (format == 'p')
		count += ft_print_ptr(va_arg(args, void *));
	if (format == 'd' || format == 'i')
		count += ft_print_int(va_arg(args, int));
	if (format == 'u')
		count += ft_print_unsig(va_arg(args, unsigned int));
	if (format == 'x' || format == 'X')
		count += ft_print_hex(va_arg(args, unsigned int), format);
	if (format == '%')
		count += ft_print_char('%');
	return (count);
}
