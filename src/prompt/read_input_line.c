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
    printf("\n================= print_tokens ======================\n");
    while (current)
    {
        printf("Type: %d, Value: %s\n", current->type, current->value);
        current = current->next;
    }
}

void print_envp(t_envp *head)
{
    t_envp *current = head;
    printf("\n================= print_envp ======================\n");
    while (current)
    {
        printf("%s%s%s\n", current->name, "=", current->envp);
        current = current->next;
    }
}


void print_env_var(char **arr)
{
    int i = 0;
    printf("\n================= env_arr ======================\n");
    while (arr[i])
    {
        printf("%s\n", arr[i]);
        i++;
    }
}

void print_cmd(t_app **shell)
{
    int i = 0;
    t_cmd *head;
    t_redir *redir;

    head = (*shell)->cmd;
    printf("\n================= print_cmd ======================\n");
    while (head != NULL)
    {
        printf("while: [%d]\n",i);
        int j = 0;
        while (head->args && head->args[j])
        {
            printf("j: arg: [%d] [%s]\n", j, head->args[j]);
            printf("is valid cmd: [%d]\n", head->is_valid_cmd);
            j++;
        }
        redir = head->redirs;
        while (redir != NULL)
        {
            printf("file: %s", redir->value);
            if (redir->type == REDIR_IN)
            {
                printf(" REDIR_IN");
            }
            else if (redir->type == REDIR_OUT)
            {
                printf(" REDIR_OUT");
            }
            else if (redir->type == APPEND)
            {
                printf(" APPEND");
            }
            else if (redir->type == HEREDOC)
            {
                printf(" HEREDOC");
            }
            else {
                printf(" FUCK");
            }
            printf("\n");
            redir = redir->next;
        }
        // printf("input: [%d] %s\n",i, head->input);
        // printf("output: [%d] %s\n",i, head->output);
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
        handle_signal_main();
        build_env_into_2d_arr(shell);
        create_prompt_path(shell);
        input = readline(shell->prompt);
        if (input == NULL)
        {
            printf("exit\n");
            break;
        }
        add_history(input);
        lexing_inputs_data(shell, input);
        parse_tokens(shell);
        ft_execute(shell);
        // print_tokens(shell);
        // print_cmd(&shell);
        // print_envp(shell->envp);
        // print_env_var(shell->env_var);
        close_child_fds(shell);
        close_fd(&shell->child_fds.dup2_in);
        close_fd(&shell->child_fds.dup2_out);
        free_list(shell);
	}
	exit_with_error(shell, shell->last_exit_code, NULL);
}
