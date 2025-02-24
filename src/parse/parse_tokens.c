/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 10:21:50 by marvin            #+#    #+#             */
/*   Updated: 2025/02/13 10:21:50 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool parse_tokens(t_app *shell)
{
    t_token *token;
    char    *temp;
    bool    iswriten;
    t_cmd    *head = NULL;
    t_cmd    *cmd = NULL;

    if (!shell || !shell->tokens)
        return false;
    iswriten = true;
    token = shell->tokens;
    cmd = create_new_cmd();
    if (!cmd)
        return false;
    while (token != NULL)
    {
        if (token->type == CMD)
        {
            cmd->cmd = parse_command(shell, token->value);
            if (!cmd->cmd)
                return (free(cmd), false);
            if ((!token->next || token->next->type != ARG))
            {
                cmd->args = extract_arguments(token, token->value);
                if (!cmd->args)
                    return NULL;
            }
        }
        else if (token->type == ARG && iswriten)
        {
            cmd->args = extract_arguments(token, token->prev->value);
            if (!cmd->args)
                return NULL;
            iswriten = false;
        }
        else if (token->type == PIPE && token->next)
        {
            add_cmd_back(&head, cmd);
            cmd = create_new_cmd();
            iswriten = true;
        }
        else if (token->type == REDIR_IN && token->next)
        {
            cmd->input = ft_strdup(token->next->value);
            if (!cmd->input)
                return false;
            token = token->next;
        }
        else if (token->type == REDIR_OUT && token->next)
        {
            cmd->output = ft_strdup(token->next->value);
            if (!cmd->output)
                return false;
            token = token->next;
        }
        else if (token->type == VAR)
        {
            if (!is_valid_brackets(token->value, '('))
            {
                temp = getenv(ft_strchr(token->value, '$', true));
                cmd->args = create_expanded_args(cmd->cmd, temp, 2);
                if (!cmd->args)
                    return false;
            }
            else if (is_valid_brackets(token->value, '(') && is_valid_brackets(token->value, ')'))
            {
                temp = extract_subcommand(token->value);
                char *executed_var = execut_subcommand(shell, temp);
                cmd->args = create_expanded_args(cmd->cmd, executed_var, 2);
                if (!cmd->args)
                    return false;
            }
        }
        else if (token->type == APPEND)
        {

        }
        else if (token->type == QUOTE)
            printf("QUOTE: %s\n",token->value);
        token = token->next;
    }
    add_cmd_back(&head, cmd);
    shell->cmd = head;
    return true;
}