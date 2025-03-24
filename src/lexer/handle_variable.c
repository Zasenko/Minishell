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
    int is_quote = false;
    char *result;

    if (input[*i] == '(')
    {
        (*i)++;
        skip_spases(input, i);
        start = *i;
        is_quote = true;
    }
    while (input[*i])
	{
        if (is_quote && input[*i] == ' ')
        {
            result = ft_substr(input ,start, *i - start);
            skip_spases(input, i);
            if (input[*i] == ')')
                return result;
        }
        else if (input[*i] == ' ' || input[*i] == '\"' || input[*i] == ')' 
            || input[*i] == '$' || input[*i] == '\'' || input[*i] == '/')
            break;
		(*i)++;
	}
    return ft_substr(input ,start, *i - start);
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

int	write_str_without_end(char *dest, char *src, int *i)
{
    int len = 0;

	while (src[len])
	{
		dest[*i] = src[len];
		(*i)++;
        len++;
	}
	return (len);
}

char *get_status_var(int status)
{
    char *result;

    result = ft_itoa(status);
    if (!result)
        return NULL;
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
    result = get_word_from_quotes(var_val->envp);
    if (!result)
        return NULL;
    return result;
}
char *get_expanded_var(t_app *shell, char *var)
{
    char *result;

    if (!var)
        return NULL;
    result = execut_subcommand(shell, var);
    if (!result)
        return NULL;
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
    else if (input[*i] != '(' && input[*i] != '?')
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
    else if (input[*i] == '(')
    {
        var = var_extractor(input, i);
        if (var)
        {
            result = get_expanded_var(shell, var);
            if (!result)
                return ft_strdup("");
            free(var);
            (*i)++;
        }
    }
    else if (input[*i] == '?')
    {
        (*i)++;
        result = get_status_var(shell->last_exit_code);
        if (!result)
            return ft_strdup("");
    } 
    return result;
}
