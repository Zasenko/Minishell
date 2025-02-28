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

char	*var_extractor(const char *input, int *i)
{
    int start = *i;

    if (input[*i] == '(')
    {
        (*i)++;
        start = *i;
    }
    while (input[*i])
	{
        if (input[*i] == ' ' || input[*i] == '\"' || input[*i] == ')' 
            || input[*i] == '$')
            break;
		(*i)++;
	}
    return ft_substr(input ,start, *i - start);
}

char *extract_word_from_quotes(char *input)
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

char *get_env_var(char *var)
{
    char *result;
    char *var_val;

    if (!var)
        return NULL;

    var_val = getenv(var);
    if (!var_val)
        return NULL;
    result = extract_word_from_quotes(var_val);
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

int get_general_length(t_app *shell, char *input)
{
    char    *res_val = NULL;
    char    *var = NULL;
    int     length = 0;
    int     i = 0;  
    char    quote = 0;

    if (!shell || !input)
        return 0;
    while (input[i])
    {
        if (!quote && input[i] == '\"')
            quote = input[i];

        if (input[i] != quote && input[i] != '$')
        {
            length++;
            i++;
        }
        else if (input[i] == '$')
        {
            if (input[i + 1] == '\0')
                break;
            i++;
            if (input[i] != '(' && input[i] != '?')
            {
                var = var_extractor(input, &i);
                if (var)
                {
                    res_val = get_env_var(var);
                    if (res_val)
                    {
                        length += ft_strlen(res_val);
                        free(res_val);
                    }
                    free(var);
                }
            }
            else if (input[i] == '(')
            {
                var = var_extractor(input, &i);
                if (var)
                {
                    res_val = get_expanded_var(shell, var);
                    if (res_val)
                    {
                        length += ft_strlen(res_val);
                        free(res_val);
                        i++;
                    }
                    free(var);
                }
            }
            else if (input[i] == '?')
            {
                i++;
                var = get_status_var(shell->last_exit_code);
                if (var)
                {
                    length += ft_strlen(var);
                    free(var);
                }
            }
        }
        else
            i++;
    }
    return length;
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

char *parse_words(t_app *shell, char *input)
{
    int     i = 0;
    int     len = 0;
    char    quote = 0;
    char    *result;
    char    *res_val = NULL;
    char    *var = NULL;

    if (!input)
        return NULL;
    result = (char*)malloc((get_general_length(shell, input) + 1) * sizeof(char));
    if (!result)
        return NULL;
    while (input[i])
    {
        if (!quote && input[i] == '\"')
            quote = input[i];
        if (input[i] != quote && input[i] != '$')
        {
            result[len] = input[i];
            len++;
            i++;
        }
        else if(input[i] == '$')
        {
            i++;
            if (input[i] != '(' && input[i] != '?')
            {
                var = var_extractor(input, &i);
                if (var)
                {
                    res_val = get_env_var(var);
                    if (res_val)
                    {
                        write_str_without_end(result, res_val, &len);
                        free(res_val);
                    }
                    free(var);
                }
            }
            else if (input[i] == '(')
            {
                var = var_extractor(input, &i);
                if (var)
                {
                    res_val = get_expanded_var(shell, var);
                    if (res_val)
                    {
                        write_str_without_end(result, res_val, &len);
                        free(res_val);
                        i++;
                    }
                    free(var);
                }
            }
            else if (input[i] == '?')
            {
                i++;
                var = get_status_var(shell->last_exit_code);
                if (var)
                {
                    write_str_without_end(result, var, &len);
                    free(var);
                }
            }
        }
        else
            i++;
    }
    result[len] = '\0';
    return result;
}


char **extract_args(t_app *shell, t_token *token, char *cmd)
{
    int     args_count;
    int     i = 1;
    char    **result;
    char    *temp;

    if (!shell || !token || !cmd)
        return NULL;

    args_count = count_types(token, ARG);
    result = (char**)malloc((args_count + 2) * sizeof(char*));
    if (!result)
        return NULL;

    result[0] = ft_strdup(cmd);
    if (!result[0])
        return NULL;

    while (token)
    {
        if (token->type == ARG)
        {
            if (is_there_quote(token->value))
            {
                if (is_there_valid_var(token->value) && ft_strchr(token->value, '\"', false))
                {
                    result[i] = parse_words(shell, token->value);
                    if (!result[i])
                        return false;
                }
                else
                {
                    temp = extract_word_from_quotes(token->value);
                    result[i] = ft_strdup(temp);
                    free(temp);
                    if (!result[i])
                        return NULL;
                }
            }
            else
            {
                if (is_there_valid_var(token->value))
                {
                    result[i] = parse_words(shell, token->value);
                    if (!result[i])
                        return false;
                }
                else
                {
                    result[i] = ft_strdup(token->value);
                    if (!result[i])
                        return NULL;
                }
            }
            i++;
        }
        token = token->next;
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
            cmd->args = extract_args(shell, token, cmd->cmd);
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
        else if (token->type == APPEND)
        {

        }
        token = token->next;
    }
    add_cmd_back(&head, cmd);
    shell->cmd = head;
    return true;
}