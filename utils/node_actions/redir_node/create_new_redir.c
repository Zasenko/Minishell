/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_new_redir.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibondarc <ibondarc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 17:55:11 by ibondarc          #+#    #+#             */
/*   Updated: 2025/02/12 17:55:11 by ibondarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_redir	*create_new_redir(void)
{
	t_redir	*new;

	new = malloc(sizeof(t_redir));
	if (!new)
		return (NULL);
	new->value = NULL;
	new->type = -1;
	new->fd = -1;
	new->is_ambiguous = false;
	new->err_name = NULL;
	new->stop_word = NULL;
	new->next = NULL;
	new->hd_with_quotes = false;
	return (new);
}
