/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibondarc <ibondarc@student.42dzasenko>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 12:06:11 by ibondarc          #+#    #+#             */
/*   Updated: 2025/02/05 12:06:11 by ibondarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	print_message(char *message, bool is_green)
{
	if (is_green)
		printf("%s%s %s\n", GREEN, message, RESET);
	else
		printf("%s%s %s\n", RED, message, RESET);
}
