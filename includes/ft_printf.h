/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibondarc <ibondarc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 10:43:46 by ibondarc          #+#    #+#             */
/*   Updated: 2025/01/30 14:36:47 by ibondarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include "./libft.h"
# include <limits.h>
# include <stdarg.h>
# include <stdint.h>
# include <unistd.h>

int	ft_printf(const char *format, ...);
int	ft_print_char(int c);
int	ft_handle_args(va_list args, char format);
int	ft_print_unsig(unsigned int n);
int	ft_print_ptr(void *ptr);
int	ft_print_hex(unsigned int n, char format);
int	ft_print_str(char *s);
int	ft_print_int(int n);
int	ft_puthex(uintptr_t n, char *format);

#endif
