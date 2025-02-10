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

void signal_hendler(int sig)
{
    if (sig == SIGINT)  
    {
        g_signal = SIGINT;  
        printf("\n"); 
        rl_on_new_line();
        rl_replace_line("", 0);
        rl_redisplay(); 
    }
    else if (sig == SIGQUIT) 
    {
        g_signal = SIGQUIT;  
        printf("Quit\n");  
    }
}

void handle_signal(void)
{
    signal(SIGINT, signal_hendler);
    signal(SIGQUIT, signal_hendler);
}