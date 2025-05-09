/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_free.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibondarc <ibondarc@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 13:49:08 by dzasenko          #+#    #+#             */
/*   Updated: 2025/05/09 14:44:07 by ibondarc         ###   ########.fr       */
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
