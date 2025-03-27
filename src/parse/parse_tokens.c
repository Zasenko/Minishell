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


char **extract_arguments(t_token *token)
{
    char    **result;
    int     args_count;
    int     i = 0;
    
    args_count = count_types(token, ARG)  + 1;
    // printf("args_count: %d\n", args_count);
    result = ft_calloc(args_count,  sizeof(char*));
    if (!result)
        return NULL;
    while (token && i < args_count)
    {
        if (token->type == PIPE)
            break;
        else if (token->type == REDIR_IN || token->type == REDIR_OUT
            || token->type == APPEND || token->type == HEREDOC)
        {
                token = token->next;
        }
        else if (token->type == ARG)
        {
            if (token->next && !ft_strlen(token->value))
            {
                printf("nothing");
                result[i] = ft_strdup(token->next->value);
                if (!result[i])
                    return NULL;
                token = token->next;
            }
            else
            {
                result[i] = extract_word_from_quotes(token->value);
                if (!result[i])
                    return false;
            }
            i++;
        }
        token = token->next;
    }
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
    if (!cmd || !shell->is_valid_syntax)
        return false;
    while (token != NULL)
    {
        if (token->type == ARG && iswriten)
        {
            cmd->is_valid_cmd = true;
            cmd->args = extract_arguments(token);
            cmd->cmd = parse_command(shell, cmd->args[0]);
            if (!cmd->cmd)
            {
                cmd->is_valid_cmd = false;
            }
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
        else if (token->type == HEREDOC)
        {
            redir = create_new_redir();
            if (!redir)
                return false;
            if (is_there_quote(token->next->value))
            {
                redir->type = HEREDOC;
                redir->heredock_with_quotes = true;
                redir->stop_word = extract_word_from_quotes(token->next->value);
            }
            else
            {
                redir->type = HEREDOC;
                redir->stop_word = ft_strdup(token->next->value);
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