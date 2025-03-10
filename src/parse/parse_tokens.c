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
            || input[*i] == '$' || input[*i] == '\'')
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

char *get_env_var(t_envp *envp, char *var)
{
    char *result;
    t_envp *var_val;

    if (!var)
        return NULL;

    var_val = find_envp_node(envp, var);
    if (!var_val)
        return NULL;
    result = extract_word_from_quotes(var_val->envp);
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
                    res_val = get_env_var(shell->envp, var);
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
    int i = 0, len = 0;
    char *result;
    char *res_val = NULL;
    char *var = NULL;
    bool is_dq_open = false; 
    bool is_sq_open = false; 

    if (!input)
        return NULL;
    
    result = (char *)malloc((get_general_length(shell, input) + 1) * sizeof(char));
    if (!result)
        return NULL;

    while (input[i]) 
    {
        if (input[i] == '\'' && !is_dq_open) 
        {
            is_sq_open = !is_sq_open; 
            i++;
        } 
        else if (input[i] == '\"' && !is_sq_open) 
        {
            is_dq_open = !is_dq_open; 
            i++;
        } 
        else if (input[i] == '$' && (!is_sq_open || is_dq_open)) 
        {
            if (input[i + 1] == ' ' || input[i + 1] == '\0' ||  input[i + 1] == '\"'
                || input[i + 1] == '$' || input[i + 1] == '\t' || input[i + 1] == '\'') 
            {
                result[len] = input[i];
                len++;
            } 
            i++;
            if (input[i] != '(' && input[i] != '?')
            { 
                var = var_extractor(input, &i);
                if (var) 
                {
                    res_val = get_env_var(shell->envp, var);
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
        {
            result[len] = input[i];
            len++;
            i++;
        }
    }
    result[len] = '\0';
    return result;
}


char **extract_args(t_app *shell, t_token *token, char *cmd)
{
    int     args_count;
    int     i = 1;
    char    **result;

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
        if (token->type == PIPE)
            break;
        else if (token->type == REDIR_IN || token->type == REDIR_OUT
            || token->type == APPEND)
        {
                token = token->next;
        }
        else if (token->type == ARG)
        {
            result[i] = parse_words(shell, token->value);
            if (!result[i])
                return false;
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
    t_cmd   *head = NULL;
    t_cmd   *cmd = NULL;
    t_redir *redir = NULL;
    char    *temp;

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
            if (ft_strchr(token->value, '$', false))
            {
                if (is_there_quote(token->value))
                {
                    temp = parse_words(shell, extract_word_from_quotes(token->value));
                    if (!temp)
                        return false;
                }
                else
                {
                    temp = parse_words(shell, token->value);
                    if (!temp)
                        return false;
                }
            }
            else
            {
                temp = parse_command(shell, token->value);
                if (!temp)
                    return false;
            }
            if ((!token->next || token->next->type != ARG))
            {
                cmd->args = extract_args(shell, token, temp);
                if (!cmd->args)
                    return false;
            }
        }
        else if (token->type == ARG && iswriten)
        {
            cmd->args = extract_args(shell, token, temp);
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
                redir->type = OUT_FILE;
                redir->value = extract_word_from_quotes(token->next->value);
            }
            else
            {
                redir->type = OUT_FILE;
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