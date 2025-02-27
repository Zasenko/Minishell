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

void print_tokens(t_app *shell)
{
    t_token *current = shell->tokens;
    while (current)
    {
        printf("Type: %d, Value: %s\n", current->type, current->value);
        current = current->next;
    }
}

void print_envp(t_envp *head)
{
    t_envp *current = head;
    while (current)
    {
        printf("%s%s%s\n", current->name, "=", current->envp);
        current = current->next;
    }
}

void print_cmd(t_app **shell)
{
    int i = 0;
    t_cmd *head;

    head = (*shell)->cmd;
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
    char    *input;

    if (!shell)
        return ;
    while (1)
    {
        build_env_into_2d_arr(shell);
        create_prompt_path(shell);
        input = readline(shell->prompt);
        if (input)
        {
            add_history(input);
            lexing_inputs_data(shell, input);
            parse_tokens(shell);
            ft_execute(shell);
            // print_tokens(shell);
            // print_cmd(&shell);
            // print_envp(shell->envp);
            free_list(shell);
        }
        else 
            break;
	}
	exit_with_error(shell, 1, NULL);
}
