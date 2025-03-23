/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 15:40:12 by marvin            #+#    #+#             */
/*   Updated: 2025/02/17 15:40:12 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void skip_spases(char *input, int *i)
{
    while (input[*i] == 32 || input[*i] == 9)
        (*i)++;
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


char *ft_devide_string(char *input, int *i, char delim, bool *is_open_q)
{
    char *res;
    int j;
    int len;

    if (!input)
        return NULL;
    len = 0;
    while (input[len] != delim)
    {
        len++;
        if (input[len] == '\"')
            *is_open_q = !(*is_open_q);
    }
    res = ft_calloc((len + 1), sizeof(char));
    j = 0;
    while (j < len)
    {
        res[j] = input[j];
        j++;
        (*i)++;
    }
    return res;
}

void join_partitions(t_app *shell, char **dest, char *input)
{
    char    *expanded;
    char    *temp;
    int     j = 0;
    int     start;
    bool    is_sq = false;

    *dest = ft_strdup(""); 
    while (input[j])
    {
        start = j; 
        while (input[j])
        {
            if (input[j] == '\'')
                is_sq = !is_sq;
            else if (input[j] == '$' && !is_sq)
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

char *extract_word(t_app *shell, char *input, int *i)
{
    char    *part;
    char    *result = NULL;

    part = divide_into_parts(input, i);
    // printf("part: %s\n", part);
    if (!part) 
        return NULL;
    if (!ft_strchr(part, '$', false))
        return part;
    if (ft_strchr(part, '\"', false) || ft_strchr(part, '\'', false))
    {
        if (is_possible_expand(part))
            join_partitions(shell, &result, part);
        else
            result = ft_strdup(part);
    }
    else
    {
        // if (is_there_valid_var(part))
            join_partitions(shell, &result, part);
        // else
        //     result = ft_strdup(part);
    }
    free(part);
    return result;
}

bool define_valid_string(char *input) 
{
    int i = 0;
    bool sing_quote = true;
    bool doub_quote = true;

    while (input[i]) 
    {
        if (input[i] == '\"') 
        {
            if (sing_quote) 
                doub_quote = !doub_quote;
        } 
        else if (input[i] == '\'') 
        {
            if (doub_quote)
                sing_quote = !sing_quote;
        }
        i++;
    }
    return (sing_quote && doub_quote);
}

