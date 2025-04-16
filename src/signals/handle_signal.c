/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler_signal.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 11:06:44 by marvin            #+#    #+#             */
/*   Updated: 2025/02/07 11:06:44 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int g_signal = 0;

int last_signal_status(void)
{
    return (g_signal);
}

void signal_new_line(void)
{
    printf("\n"); 
    rl_on_new_line();
    rl_replace_line("", 0);
    rl_redisplay(); 
}

void signal_hendler(int sig)
{
    // printf("MAIN SIG: %d\n", sig);
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

void handle_signal(void)
{
    g_signal = 0;
    signal(SIGINT, &signal_hendler);
    signal(SIGQUIT, &signal_hendler);
}

void signal_hendler_in_child(int sig)
{
    if (sig == SIGINT)
    {
        g_signal = SIGINT;  
        ft_putstr_fd("\n", 1);
    }
    else if (sig == SIGQUIT)
    {
        g_signal = SIGQUIT;
    }
}

void handle_child_signal(void)
{
    g_signal = 0;
    signal(SIGINT, &signal_hendler_in_child);
    signal(SIGQUIT, &signal_hendler_in_child);
    // signal(SIGPIPE, SIG_IGN); // иначе сигналы от мёртвых пайпов валят всю цепь

}