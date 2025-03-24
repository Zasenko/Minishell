/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 15:47:48 by marvin            #+#    #+#             */
/*   Updated: 2025/02/17 15:47:48 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool is_possible_expand(char *input)
{
    int  i = 0;
    bool is_dq_open = false;
    bool is_sq_open = false;

    if (!input)
        return false;

    while (input[i])
    {
        if (input[i] == '\"' && !is_sq_open)
            is_dq_open = !is_dq_open;
        else if (input[i] == '\'' && !is_dq_open)
            is_sq_open = !is_sq_open;
        else if (input[i] == '$' && !is_sq_open)
            return true;
        i++;
    }
    return false;
}

char *divide_into_parts(char *input, int *i)
{
    bool    is_dq_open = false;
    bool    is_sq_open = false;
    int     start;
    
    start = *i;
    while (input[*i])
    {
        if (input[*i] == '\'' && !is_dq_open) 
            is_sq_open = !is_sq_open;
        else if (input[*i] == '\"' && !is_sq_open) 
            is_dq_open = !is_dq_open;
        else if ((input[*i] == ' ' || input[*i] == '\t' || input[*i] == '>'  // to do >> <<
            || input[*i] == '<' || input[*i] == '|') && !is_dq_open && !is_sq_open)
            break;
        (*i)++;
    }
    return ft_substr(input, start, *i - start);
}

void join_partitions(t_app *shell, char **dest, char *input)
{
    char    *expanded;
    char    *temp;
    int     j = 0;
    int     start;
    bool    sing_quote = false;
    bool    doub_quote = false;

    *dest = ft_strdup(""); 
    while (input[j])
    {
        start = j; 
        while (input[j])
        {
            if (input[j] == '\'' && !doub_quote)
                sing_quote = !sing_quote;
            if (input[j] == '\"' && !sing_quote)
                doub_quote = !doub_quote;
            else if (input[j] == '$' && !sing_quote)
                break;
            j++;
        }
        if (start != j)
        {
            temp = ft_strjoin(*dest, ft_substr(input, start, j - start));
            free(*dest);
            *dest = temp;
        }
        if (input[j] == '$')
        {
            expanded = expand_words(shell, input, &j);
            temp = ft_strjoin(*dest, expanded);
            free(*dest);
            *dest = temp;
        }
    }
}

bool handle_command(t_app *shell, t_token *token, char *input, int *i)
{
    char    *part;
    char    **temp;
    char    *result = NULL;
    int     j;

    part = divide_into_parts(input, i);
    // printf("part: %s\n", part);
    if (!part) 
        return NULL;
    if (!ft_strchr(part, '$', false))
    {
        token->value = part;
        token->type = ARG;
        return true;
    }
    if (ft_strchr(part, '\"', false) || ft_strchr(part, '\'', false))
    {
        if (is_possible_expand(part))
            join_partitions(shell, &token->value, part);
        else
        {
            token->value = ft_strdup(part);
            if (!token->value)
                return false;
        }
        token->type = ARG;
    }
    else if (token->prev && token->prev->type == REDIR_OUT)
    {
        join_partitions(shell, &result, part);
        temp = ft_split(result, ' ');
        j = 0;
        while (temp[j])
            j++;
        if (j == 0 || j > 1 || !ft_strlen(temp[0]))
        {
            ft_putstr_fd(part, 2);
            ft_putstr_fd(": ambiguous redirect\n", 2);
            shell->last_exit_code = 1;
            free(part);
            return false;
        } 
        else
            token->value =  result;
        token->type = ARG;
    }
    else
    {
        join_partitions(shell, &result, part);
        temp = ft_split(result, ' ');
        j = 0;
        while (temp[j])
        {
            if (j == 0)
            {
                token->value = temp[j];
                token->type = ARG;
            }
            else
            {
                t_token *new = create_new_token();
                new->value = temp[j];
                new->type = ARG;
                add_token_back(&token, new);     
            }
           j++;
        }
    }
    free(part);
    return true;
}
