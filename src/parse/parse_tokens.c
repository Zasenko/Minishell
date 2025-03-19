//* ************************************************************************** */
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

bool is_there_quote(char *str)
{
    while (*str)
    {
        if (*str == '\'' || *str == '\"')
            return true;
        str++;
    }
    return false;
}

char *extract_word_from_quotes(char *input) 
{
    int   i = 0, j = 0;
    int   len;
    char  *res;
    char  quote = 0;

    if (!input)
        return NULL;

    len = ft_strlen(input);
    res = (char *)malloc((len + 1) * sizeof(char));
    if (!res)
        return NULL;

    while (input[i])
    {
        if (!quote && (input[i] == '\'' || input[i] == '\"')) 
            quote = input[i];  
        else if (quote && input[i] == quote) 
            quote = 0; 
        else
            res[j++] = input[i];
        
        i++;
    }
    res[j] = '\0';
    return res;
}


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
        result[i] = extract_word_from_quotes(token->value);
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
    t_cmd   *head = NULL;
    t_cmd   *cmd = NULL;
    t_redir *redir = NULL;

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
            // printf("CMD\n");
            cmd->cmd = ft_strdup(token->value);
            // printf("value: %s\n", cmd->cmd);
            if ((!token->next || token->next->type != ARG))
            {
                cmd->args = extract_arguments(shell->tokens, token->value);
                if (!cmd->args)
                    return false;
            }
        }
        else if (token->type == ARG && iswriten)
        {
            // printf("ARG\n");
            // printf("value: %s\n", token->value);
            cmd->args = extract_arguments(shell->tokens, token->prev->value);
            if (!cmd->args)
                return false;
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
            redir = create_new_redir();
            if (!redir)
                return false;
            if (is_there_quote(token->next->value))
            {
                redir->type = REDIR_IN;
                redir->value = extract_word_from_quotes(token->next->value);
            }
            else
            {
                redir->type = REDIR_IN;
                redir->value = ft_strdup(token->next->value);
            }
            add_redir_back(&cmd->redirs, redir);
            token = token->next;
        }
        else if (token->type == REDIR_OUT && token->next)
        {
            redir = create_new_redir();
            if (!redir)
                return false;
            if (is_there_quote(token->next->value))
            {
                redir->type = REDIR_OUT;
                redir->value = extract_word_from_quotes(token->next->value);
            }
            else
            {
                redir->type = REDIR_OUT;
                redir->value = ft_strdup(token->next->value);
            }
            add_redir_back(&cmd->redirs, redir);
            token = token->next;
        }
        else if (token->type == APPEND)
        {
            redir = create_new_redir();
            if (!redir)
                return false;
            if (is_there_quote(token->next->value))
            {
                redir->type = APPEND;
                redir->value = extract_word_from_quotes(token->next->value);
            }
            else
            {
                redir->type = APPEND;
                redir->value = ft_strdup(token->next->value);
            }
            add_redir_back(&cmd->redirs, redir);
            token = token->next;
        }
        token = token->next;
    }
    add_cmd_back(&head, cmd);
    shell->cmd = head;
    return true;
}