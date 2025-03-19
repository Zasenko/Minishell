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

bool handle_command(t_app *shell, t_token *token, t_token *prev, char *input, int *i)
{
    token->value = extract_word(shell, input, i);
    // if (!temp)
    //     return false;
    // if (ft_strchr(temp, '\"', false))
    // {
    //     token->value = get_word_from_quotes(temp);
    //     free(temp);
    //     if (!token->value)
    //         return false;
    // }
    // else 
    //     token->value = temp;
    skip_spases(input, i);
    if ((prev && prev->type == REDIR_IN) || (prev && prev->type == HEREDOC))
        token->type = ARG;
    else if ((prev && prev->type == REDIR_OUT) || (prev && prev->type == APPEND))
        token->type = ARG;
    else 
    { 
        if (prev && prev->type != CMD && prev->type != ARG)
        {
            token->type = CMD;
        }
        else 
        {
            if (!prev)
                token->type = CMD;
            else
                token->type = ARG;
        }
    }
    return true;
}