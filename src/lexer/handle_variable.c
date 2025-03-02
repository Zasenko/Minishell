/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_variable.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 15:41:07 by marvin            #+#    #+#             */
/*   Updated: 2025/02/17 15:41:07 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool handle_variable(t_token *token, t_token *prev, char *input, int *i)
{
    if (!prev)
        token->type = CMD;
    else
        token->type = ARG;
    token->value = extract_word(input, i);
    if (!token->value)
        return false;
    return true;
}