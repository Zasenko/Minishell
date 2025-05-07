/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_free.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzasenko <dzasenko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 13:49:08 by dzasenko          #+#    #+#             */
/*   Updated: 2025/05/06 13:52:04 by dzasenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_heredoc(t_heredoc *hd)
{
	if (hd->dest)
	{
		free(hd->dest);
		hd->dest = NULL;
	}
	if (hd->temp)
	{
		free(hd->temp);
		hd->temp = NULL;
	}
}
