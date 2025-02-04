/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_shell.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 21:24:36 by marvin            #+#    #+#             */
/*   Updated: 2025/02/03 21:24:36 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_app  *initialize_shell(void)
{
    t_app *new;

    new = malloc(sizeof(t_app));
    if (!new)
        return NULL;
    new->path = ft_split(getenv("PATH"), ':');
    if (!new->path)
        return NULL;
    new->user = getenv("USER");
    if (!new->user)
    {
        new->user = ft_strdup("unknown");
        if (!new->user)
            return NULL;
    }
    new->name = getenv("NAME");
    if (!new->name)
    {
        new->name = ft_strdup("shell-root");
        if (!new->name)
            return NULL;
    }
    new->pwd = getcwd(NULL, 0);
    if (!new->pwd)
    {
        new->pwd = ft_strdup("");
        if (!new->pwd)
            return NULL;
    }
    new->args = NULL;
	new->input = NULL;
	new->output = NULL;
	new->next = NULL;
    new->prev = NULL;
	new->append = 0;
    return new;
}
