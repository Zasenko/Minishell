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

char **extract_arguments(t_token *token, char *cmd)
{
    char    **result;
    int     args_count;
    int     i = 0;
    
    args_count = count_types(token, ARG) + 2;
    result = (char**)malloc(args_count * sizeof(char*));
    if (!result)
        return NULL;
    while (token && i < args_count - 1)
    {
        if (i == 0 && token->type == ARG)
        {
            result[i] = ft_strdup(cmd);
            if (!result[i])
                return NULL;
            i++;
        }
        result[i] = ft_strdup(token->value);
        if (!result[i])
            return NULL;
        token = token->next;
        i++;
    }
    result[i] = NULL;
    return result;
}

bool parse_tokens(t_app *shell)
{
    t_token *token;
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
        else if (token->type == QUOTE)
            printf("QUOTE: %s\n",token->value);
        token = token->next;
    }
    add_cmd_back(&head, cmd);
    shell->cmd = head;
    return true;
}