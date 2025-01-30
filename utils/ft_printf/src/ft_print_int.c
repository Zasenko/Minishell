/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_int.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibondarc <ibondarc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 19:11:05 by igoryan           #+#    #+#             */
/*   Updated: 2025/01/30 13:45:00 by ibondarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/ft_printf.h"

int	ft_print_int(int n)
{
	char	*result;
	int		count;

	result = ft_itoa(n);
	count = ft_print_str(result);
	free(result);
	return (count);
}
