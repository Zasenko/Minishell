/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_input_line.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 19:00:55 by marvin            #+#    #+#             */
/*   Updated: 2025/02/12 19:00:55 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void print_tokens(t_token *head)
{
    t_token *current = head;
    while (current)
    {
        printf("Type: %d, Value: %s\n", current->type, current->value);
        current = current->next;
    }
}


void read_input_line(t_app *shell)
{
    char *input;

    if (!shell)
        return ;
    if (!create_prompt_path(shell))
    {
        exit_with_error(shell, 1);
    }
    while (1)
    {
        input = readline(shell->prompt);
        if (!input)
			exit_with_error(shell, 1);
		add_history(input);
		lexing_inputs_data(shell, input);
        parse_tokens(shell);
        // print_tokens(shell->tokens);
		ft_execute(shell);
        // free_list(shell);
	}
}