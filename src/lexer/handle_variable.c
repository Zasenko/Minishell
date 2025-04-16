// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   handle_variable.c                                  :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2025/02/17 15:41:07 by marvin            #+#    #+#             */
// /*   Updated: 2025/02/17 15:41:07 by marvin           ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

#include "../../includes/minishell.h"

char	*var_extractor(char *input, int *i)
{
    int start = *i;
    char *result;

    while (input[*i])
	{
        if (input[*i] == ' ' || input[*i] == '\"' || input[*i] == ')' 
            || input[*i] == '$' || input[*i] == '\'' || input[*i] == '/'
            || input[*i] == 46 || input[*i] == '?')
            break;
		(*i)++;
	}
    result = ft_substr(input ,start, *i - start);
    if (!result)
        return NULL;
    return result;
}

bool is_there_valid_var(char *str)
{
    while (*str)
    {   
        if (*str == '\0' || *str == '$'
            ||  *str == ' ' || *str == '\t')
            return false;
        str++;
    }
    return true;
}

char *get_word_from_quotes(char *input)
{
    int     i;
    int     len;
    char    *res;
    char    quote = 0;

    i = 0;
    len = ft_strlen(input);
    res = (char *)malloc((len + 1) * sizeof(char));
    if (!res)
        return NULL;
    while (*input)
    {
        if (!quote && (*input == '\'' || *input == '\"'))
            quote = *input;
        if (*input != quote)
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

char *get_status_var(int status)
{
    char *result;

    result = ft_itoa(status);
    if (!result)
        return NULL;
    return result;
}

char *wrap_in_quotes(char *str)
{
    int i = 0;
    int len;
    char *result;

    if (!str)
        return NULL;
    len = ft_strlen(str) + 2;
    result = ft_calloc(len + 1, sizeof(char));
    if (!result)
        return NULL;
    result[i++] = '\'';
    result[len--] = '\'';
    while (i < len)
    {
        result[i] = str[i - 1];
        i++;
    }
    return result;
}

char *get_env_var(t_envp *envp, char *var)
{
    char *result;
    t_envp *var_val;

    if (!var)
        return NULL;

    var_val = find_envp_node(envp, var);
    if (!var_val)
        return NULL;
    if (var_val->envp[0] == '\"')
    {
        result = wrap_in_quotes(var_val->envp);
        if (!result)
            return NULL;
    }
    else
    {
        result = ft_strdup(var_val->envp);
        if (!result)
            return NULL;
    }
    return result;
}

char *expand_words(t_app *shell, char *input, int *i)
{
    char    *var = NULL;
    char    *result = NULL;

    if (!shell || !input)
        return 0;
    (*i)++;
    if (input[*i] == ' ' || input[*i] == '\0' ||  input[*i] == '\"' || input[*i] == '/'
        || input[*i] == '$' || input[*i] == '\t' || input[*i] == '\'')
        result = ft_substr(input, *i - 1 , 1);
    
    if (input[*i] == '?')
    {
        (*i)++;
        result = get_status_var(shell->last_exit_code);
        if (!result)
            return ft_strdup("");
    }
    else if ((input[*i] >= 64 && input[*i] <= 90) || (input[*i] >= 97 && input[*i] <= 122))
    {
        var = var_extractor(input, i);
        if (var)
        {
            result = get_env_var(shell->envp, var);
            if (!result)
                return ft_strdup("");
            free(var);
        }
    }
    return result;
}
