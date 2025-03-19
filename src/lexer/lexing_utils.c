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

char	*ft_strcopy(char *input, int *i, char quote)
{
	char	*result;
	int		j = 0;
    bool    is_quote = false;

	if (!input)
		return NULL;
	result = (char *)malloc(sizeof(char) * (strlen(&input[*i]) + 1));
	if (!result)
		return (NULL);
	while (input[*i] && input[*i] != '|' && input[*i] != '<' && input[*i] != '>')
    {
        if (input[*i] == quote )
            is_quote = !is_quote;
        if ((input[*i] == ' ' || input[*i] == '\t') && is_quote)
            break;
        result[j++] = input[(*i)++];
    }
    result[j] = '\0';
	return (result);
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
    int     i = 0;
    bool    is_dq_open = false;
    bool    is_sq_open = false;
    
    if (!input)
        return false;

    // Ensure we only treat quote characters correctly
    char quote = (input[i] == '\'' || input[i] == '\"') ? input[i] : '\0';

    while (input[i])
    {
        if (input[i] == '\"' && !is_sq_open) 
            is_dq_open = !is_dq_open;
        else if (input[i] == '\'' && !is_dq_open) 
            is_sq_open = !is_sq_open;
        
        // Only allow expansion if we are NOT inside single quotes
        if (input[i] == '$' && !is_sq_open)
            return true;
        i++;
        // Stop if we reach the end of the quoted section
        if (quote && input[i] == quote)
            break;
    }

    return false;
}

void divide_into_words(char *input, int *i)
{
    bool    is_dq_open = false;
    bool    is_sq_open = false;

    while (input[*i] && input[*i] != '|' && input[*i] != '<' && input[*i] != '>')
    {
        if (input[*i] == '\'' && !is_dq_open) 
            is_sq_open = !is_sq_open;
        else if (input[*i] == '\"' && !is_sq_open) 
            is_dq_open = !is_dq_open;
        else if ((input[*i] == ' ' || input[*i] == '\t') && !is_dq_open && !is_sq_open)
            break;
        (*i)++;
    }
}

char *extract_word(t_app *shell, char *input, int *i)
{
    int     start;
    char    *res;
    int     j;
    
    start = *i;
    j = *i;
    divide_into_words(input, &j);
    if (!ft_strnstr(&input[start], "$", j - start))
    {
        res = ft_substr(input, start, j - start);
        if (!res)
            return NULL;
        *i += j - start;  // Move pointer forward
    }
    else
    {       
            int k = 0;
            char quote;
            while (input[k])
            {
                if (input[k] == '\'' && input[k] == '\"')
                    quote = input[k];
                k++;
            }
            if (is_possible_expand(&input[*i]))
            {
                while (input[*i] && input[*i] != '$')
                    (*i)++;
                res = ft_substr(input, start,  *i - start);
                if (!res)
                    return NULL;
                char *expanded = expand_words(shell, input, i);
                char *temp = ft_strjoin(res, expanded);
                free(res);  // Free old res
                char *final_result = ft_strjoin(temp, ft_strcopy(input, i, quote));
                free(temp); // Avoid memory leak
                return final_result;
            }
            else
                res = ft_strcopy(input, i, quote);
    }
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

