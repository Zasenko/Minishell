/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler_signal.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibondarc <ibondarc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 11:06:44 by ibondarc          #+#    #+#             */
/*   Updated: 2025/02/07 11:06:44 by ibondarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

volatile sig_atomic_t	g_signal = 0;

int	last_signal_status(void)
{
	return (g_signal);
}

void	change_signal_status(int status)
{
	g_signal = status;
}

void	signal_new_line(void)
{
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	signal_hendler(int sig)
{
	if (sig == SIGINT)
	{
		g_signal = SIGINT;
		signal_new_line();
	}
	else if (sig == SIGQUIT)
	{
		g_signal = SIGQUIT;
	}
}

void	handle_signal_main(void)
{
	g_signal = 0;
	rl_event_hook = NULL;
	signal(SIGINT, signal_hendler);
	signal(SIGQUIT, SIG_IGN);
}
