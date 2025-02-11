/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 21:24:41 by marvin            #+#    #+#             */
/*   Updated: 2025/02/10 18:02:51 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int main(int argc, char **argv, char **envp)
{
    t_app   shell;
    
    (void)argc;
    (void)argv;
    initialize_shell(&shell, envp);
    handle_signal();
    read_input_line(&shell);
    ft_execute(&shell);
    // todo: free schall + close all fds
    return 0;
}
