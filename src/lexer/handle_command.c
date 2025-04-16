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

void write_value(t_token *token, char *value, int type)
{
    token->value = value;
    token->type = type;
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
        else if ((input[*i] == ' ' || input[*i] == '\t' || input[*i] == '>'  
            || input[*i] == '<' || input[*i] == '|') && !is_dq_open && !is_sq_open)
            break;
        (*i)++;
    }
    return ft_substr(input, start, *i - start);
}

void skip_all_beafor_variable(char *input, int *j)
{
    bool    sing_quote;
    bool    doub_quote;

    sing_quote = false;
    doub_quote = false;
    while (input[*j])
    {
        if (input[*j] == '\'' && !doub_quote)
            sing_quote = !sing_quote;
        if (input[*j] == '\"' && !sing_quote)
            doub_quote = !doub_quote;
        if (input[*j] == '$' && !sing_quote)
            break;
        (*j)++;
    }
}

int join_partitions(t_app *shell, char **dest, char *input, bool *do_split)
{
    char    *expanded;
    char    *temp;
    int     j = 0;
    int     start;

    *dest = ft_strdup("");
    if (!(*dest))
        return false;
    while (input[j])
    {
        start = j; 
        skip_all_beafor_variable(input, &j);
        if (start != j)
        {
            temp = ft_strjoin(*dest, ft_substr(input, start, j - start));
            free(*dest);
            *dest = temp;
        }
        if (input[j] == '$')
        {
            expanded = expand_words(shell, input, &j);
            if (!expanded)
                return false;
            if (ft_strchr(expanded, ' ', false))
                *do_split = !(*do_split);
            temp = ft_strjoin(*dest, expanded);
            free(*dest);
            *dest = temp;
        }
    }
    return true;
}
bool handle_redir_outfile(t_app *shell, t_token *token, char *input, bool *do_split)
{
    int     j;
    char    **temp;
    char    *result;

    j = 0;
    result = NULL;
    if (!join_partitions(shell, &result, input, do_split))
        return false;
    temp = ft_split(result, ' ');
    if (!temp)
        return false;
    while (temp[j])
        j++;
    if (j == 0 || j > 1 || !ft_strlen(temp[0]))
    {
        ft_putstr_fd(input, 2);
        ft_putstr_fd(": ambiguous redirect\n", 2);
        shell->last_exit_code = 1;
        free(input);
        return false;
    } 
    else
        token->value =  result;
    token->type = ARG;
    return true;
}

bool add_expanded_value_into_node(t_token *token, char **input)
{
    int     j;
    t_token *new;

    j = 0;
    if (!input)
        return false;
    while (input[j])
    {
        if (j == 0)
            write_value(token, input[j], ARG);
        else
        {
            new = create_new_token();
            if (!new)
                return false;
            write_value(new, input[j], ARG);
            add_token_back(&token, new);     
        }
        j++;
    }
    return true;
} 
bool handle_quotes_case(t_app *shell, t_token *token, char *part)
{
    bool    do_split;
    char    **temp;

    do_split = false;
    if (define_valid_string(part))
    {
        if (!join_partitions(shell, &token->value, part, &do_split))
            return false;
        if (do_split)
        {
            temp = ft_split(token->value, ' ');
            if (!add_expanded_value_into_node(token, temp))
                return false;
        }
    }
    else
    {
        token->value = ft_strdup(part);
        if (!token->value) 
            return false;
    }
    token->type = ARG;
    return true;
}

bool handle_command(t_app *shell, t_token *token, char *input, int *i)
{
    char *part;
    char *result;
    bool    do_split;

    do_split = false;
    result = NULL;
    part = divide_into_parts(input, i);
    if (!part) 
        return false;
    if (!ft_strchr(part, '$', false))
        return (write_value(token, part, ARG), true);
    if (ft_strchr(part, '\"', false) || ft_strchr(part, '\'', false))
        return handle_quotes_case(shell, token, part);
    if (token->prev && token->prev->type == REDIR_OUT)
        return handle_redir_outfile(shell, token, part, &do_split);
    if (!join_partitions(shell, &result, part, &do_split))
        return false;
    if (!add_expanded_value_into_node(token, ft_split(result, ' ')))
        return false;
    free(part);
    return true;
}
