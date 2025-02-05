/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env_info.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 13:26:13 by marvin            #+#    #+#             */
/*   Updated: 2025/02/05 13:26:13 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool get_env_info(t_app *shell)
{
    if (!shell)
        return false;
    shell->path = ft_split(getenv("PATH"), ':');
    if (!shell->path)
        return false;
    shell->user = ft_strdup(getenv("USER"));
    if (!shell->user)
    {
        shell->user = ft_strdup("unknown");
        if (!shell->user)
            return false;
    }
    shell->name = ft_strdup(getenv("NAME"));
    if (!shell->name)
    {
        shell->name = ft_strdup("shell-root");
        if (!shell->name)
            return false;
    }
    shell->pwd = ft_strdup(getenv("PWD"));
    if (!shell->pwd)
    {
        shell->pwd = ft_strdup("");
        if (!shell->pwd)
            return false;
    }
    return true;
}
