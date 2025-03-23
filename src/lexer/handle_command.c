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

bool handle_command(t_app *shell, t_token *token, char *input, int *i)
{
    token->value = extract_word(shell, input, i);
    if (!token->value)
        return false;
    token->type = ARG;
    return true;
}
