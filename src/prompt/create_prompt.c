/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_prompt.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 20:28:34 by marvin            #+#    #+#             */
/*   Updated: 2025/02/05 20:28:34 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool create_prompt_path(t_app *shell)
{
    char    *prompt;
    char    *temp;
    int     i;

    if (!get_env_info(shell))
        return false;
    prompt = ft_strjoin(GREEN, shell->name);
    if (!prompt) 
        return false;
    i = 0;
    char    *parts[] = {"@", shell->user, RESET, ":", BLUE, shell->pwd, RESET, "$ "};
    while ( i < 8) 
    {
        temp = ft_strjoin(prompt, parts[i]);
        free(prompt);
        if (!temp)
            return false;
        prompt = temp;
        i++;
    }
    shell->prompt = prompt;
    return true;
}