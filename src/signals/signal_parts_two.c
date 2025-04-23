/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_parts_two.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibondarc <ibondarc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 10:40:53 by ibondarc          #+#    #+#             */
/*   Updated: 2025/04/23 11:09:08 by ibondarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	sigint_heredoc_handler(int sig)
{
	(void)sig;
	change_signal_status(1);
}

int	readline_event_hook(void)
{
	if (last_signal_status())
	{
		rl_done = 1;
	}
	return (0);
}

void	handle_signal_heredoc(void)
{
	change_signal_status(0);
	signal(SIGINT, sigint_heredoc_handler);
	signal(SIGQUIT, SIG_IGN);
	rl_event_hook = readline_event_hook;
}

int	readline_event_hook2(void)
{
	if (last_signal_status())
	{
		rl_done = 0;
	}
	return (0);
}

void	handle_child_signal(void)
{
	change_signal_status(0);
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}
