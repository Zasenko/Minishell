/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzasenko <dzasenko@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 13:22:59 by dzasenko          #+#    #+#             */
/*   Updated: 2025/02/12 15:41:19 by dzasenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	ft_pwd(void)
{
	char	buf[MAXPATHLEN];
	char	*dir;

	dir = NULL;
	dir = getcwd(buf, MAXPATHLEN);
	if (!dir)
		return (perror("getcwd"), errno);
	ft_putstr_fd(dir, 1);
	ft_putstr_fd("\n", 1);
	return (SUCCESS);
}
