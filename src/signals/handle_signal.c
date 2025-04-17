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

volatile sig_atomic_t g_signal = 0;//DELETE

int last_signal_status(void)
{
    return (g_signal);
}

int readline_event_hook(void)
{
    if (g_signal) {
        rl_done = 1;
    }
    return 0;
}

int readline_event_hook2(void)
{
    if (g_signal) {
        rl_done = 0;
    }
    return 0;
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

void handle_signal_main(void)
{
    g_signal = 0;
    rl_event_hook = NULL;
    signal(SIGINT, &signal_hendler);
	signal(SIGQUIT, SIG_IGN);
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


// Signal handler using sigaction
void sigint_heredoc_handler(int sig) 
{
	(void)sig;
    g_signal = 1;
}

void handle_signal_heredoc(void)
{
    g_signal = 0;
    // struct sigaction sa;
	// sa.sa_handler = sigint_heredoc_handler;
	// sigemptyset(&sa.sa_mask);
	// sa.sa_flags = 0;
	signal(SIGINT, &sigint_heredoc_handler);
	signal(SIGQUIT, SIG_IGN);
	rl_event_hook = readline_event_hook;
}