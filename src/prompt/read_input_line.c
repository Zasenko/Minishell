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

void print_cmd(t_cmd *head)
{
    int i = 0;
    while (head != NULL)
    {
        printf("cmd: [%d] %s\n",i, head->cmd);
        int j = 0;
        while (head->args[j])
        {
            printf("j: arg: [%d] %s\n", j, head->args[j]);
            j++;
        }
        printf("input: [%d] %s\n",i, head->input);
        printf("output: [%d] %s\n",i, head->output);
        i++;
        head = head->next;
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
        if (!lexing_inputs_data(shell, input))
            exit_with_error(shell, 1);
        parse_tokens(shell);
		ft_execute(shell);
        // print_cmd(shell->cmd);
        free_token_list(&shell->tokens);
        free_cmd_list(&shell->cmd);
	}
}