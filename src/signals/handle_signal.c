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

void signal_new_line(void)
{
    printf("\n"); 
    rl_on_new_line();
    rl_replace_line("", 0);
    rl_redisplay(); 
}

void signal_hendler(int sig)
{
    if (sig == SIGINT)
    {
        g_signal = SIGINT;
        signal_new_line();
    }
    // else if (sig == SIGQUIT)
    // {
    //     g_signal = SIGQUIT;
    //     printf("exit\n");
    // }
}

void handle_signal(void)
{
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
    // else if (sig == SIGQUIT)
    // {
    //     g_signal = SIGQUIT;  
    //     ft_putstr_fd("Quit", 1);
    // }
}


void handle_child_signal(void)
{
    signal(SIGINT, &signal_hendler_in_child);
    signal(SIGQUIT, &signal_hendler_in_child);
}

void signal_hendler_in_heredoc(int sig)
{
    if (sig == SIGINT)
    {
        g_signal = SIGINT;  
        ft_putstr_fd("HEREDOC SIGINT\n", 1);
    }
    else if (sig == SIGQUIT)
    {
        g_signal = SIGQUIT;  
        ft_putstr_fd("HEREDOC SIGQUIT\n", 1);
    }
}

void handle_heredoc_signal(void)
{
    // g_signal = 0;
    signal(SIGINT, &signal_hendler_in_heredoc);
    signal(SIGQUIT, &signal_hendler_in_heredoc);
}