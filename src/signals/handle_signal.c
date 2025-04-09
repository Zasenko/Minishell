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

void check_signal_exit(t_app *shell)
{
    // printf("g_signal: %d", g_signal);
    // if (g_signal == 0 )
    // {
        printf("exit\n");
        free_list(shell);
        exit(0);
    // }
}

int signal_last_code(void)
{

    return (g_signal);
}

// void check_signal_heredoc_exit(t_app *shell)
// {
//     if (g_signal != 0)
//     {
//         printf("exit\n");
//         free_list(shell);
//         exit(0);
//     }
// }

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
}

void signal_hendler_in_heredoc(int sig)
{
    // printf("signal_hendler_in_heredoc: %d\n", g_signal);
    if (sig == SIGINT)
    {
        g_signal = SIGINT;  
        printf("\n");
        close(0);
    }
    if (sig == SIGQUIT)
    {
        g_signal = SIGQUIT;  
        printf("\n"); 
        rl_on_new_line();
        rl_replace_line("", 0);
        rl_redisplay(); 
    }
}

void handle_heredoc_signal(void)
{
    g_signal = 0;
    signal(SIGINT, &signal_hendler_in_heredoc);
    signal(SIGQUIT, SIG_IGN);
}