/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_unsig.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibondarc <ibondarc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 19:37:35 by igoryan           #+#    #+#             */
/*   Updated: 2025/01/30 13:45:07 by ibondarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/ft_printf.h"

int	ft_print_unsig(unsigned int n)
{
	int	count;

	count = 0;
	if (n == 0)
		return (ft_print_char('0'));
	if (n > 9)
	{
		count += ft_print_unsig(n / 10);
		n %= 10;
	}
	count += ft_print_char((n % 10) + 48);
	return (count);
}
