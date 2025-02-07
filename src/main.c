/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 21:24:41 by marvin            #+#    #+#             */
/*   Updated: 2025/02/07 18:38:09 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// It's just a func to print list of cmd command!
// in order to understend how it works.
void print_cmd_struct(t_app *shell)
{
    int i = 0;
    if (!shell->cmd)
        return ;
    while (shell->cmd != NULL)
    {
        int j = 0;
        printf("=====[command cout: %d]========\n", i);
        while (shell->cmd->args[j])
        {
            printf("%s\n", shell->cmd->args[j]);
            j++;
        }
        shell->cmd = shell->cmd->next;
        i++;
    }
}

int main(void)
{
    t_app   shell;
    
    initialize_shell(&shell);
    handle_signal();
    read_input_line(&shell);
    print_cmd_struct(&shell);
    exit_with_error(&shell, 1);
    return 0;
}
