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

char *extract_single_string(char *input)
{
    int     i;
    int     len;
    char    *res;

    i = 0;
    len = ft_strlen(input);
    res = (char *)malloc((len - 1) * sizeof(char));
    if (!res)
        return NULL;
    i = 0;
    while (*input)
    {
        if (*input == ' ')
            break;
        if (*input != '\'')
        {
            res[i] = *input;
            input++;
            i++;
        }
        else
            input++;
    }
    res[i] = '\0';
    return res;
}

void skip_spases(char *input, int *i)
{
    while (input[*i] == 32 || input[*i] == 9)
        (*i)++;
}

void skip_quotes(char *input, int *i, char quote)
{
    while (input[*i] == quote)
        (*i)++;
}
bool is_there_valid_var(char *str)
{
    bool is_valid;

    is_valid = false;
    while (*str)
    {   
        if (*str == '$')
        {
            str++;
            is_valid = true;
            if (*str == '\0' || *str == '$' || *str == '\"'
                ||  *str == ' ' || *str == '\t')
                return false;
        }
        else
            str++;
    }
    return is_valid;
}

char *divide_into_part(char *input, int *i)
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
        else if ((input[*i] == ' ' || input[*i] == '\t') && !is_dq_open && !is_sq_open)
            break;
        (*i)++;
    }
    return ft_substr(input, start, *i - start);
}

int count_quotes(const char *input, char quote) 
{
    int count = 0;
    bool escaped = false;

    while (*input) 
    {
        if (*input == '\\' && !escaped)
            escaped = true;
        else if (*input == quote && !escaped)
            count++;
        else
            escaped = false;
        
        input++;
    }
    return count;
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

char *extract_word(t_app *shell, char *input, int *i)
{
    char    *part;
    char    *res;
    int     j;

    // printf("=========================start===============================\n");
    part = divide_into_part(input, i);
    // printf("part: %s\n",part);
    if (!ft_strchr(part, '$', false))
    {
        // printf("=========================end===============================\n");
        return part;
    }
    else
    {       
        // printf("input: %s\n", part);
        if (ft_strchr(part, '\"', false) || ft_strchr(part, '\'', false))
        {
            // printf("Expand $var with quotes \n");
            if (is_possible_expand(part) && is_there_valid_var(part))
            {
                // printf("In case where can be expande $ from quotes\n");

                j = 0;
                while (part[j] && part[j] != '$')
                    j++;
                res = ft_substr(part, 0, j);
                if (!res)
                    return NULL;
                char *expanded = expand_words(shell, part, &j);
                char *temp = ft_strjoin(res, expanded);
                free(res);  
                char *final_result = ft_strjoin(temp, ft_strdup(&part[j]));
                free(temp); 
                return final_result;
            }
            else
            {
                // printf("In case that is no able to expand $ from quotes\n");
                res = ft_strdup(part);
            }
        }
        else
        {
            // printf("Expand $var without quotes \n");
            res = expand_words(shell, part, &j);
        }
    }
    // printf("=========================end===============================\n");
    return res;
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

