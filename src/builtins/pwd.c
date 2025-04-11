/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmitryzasenko <dmitryzasenko@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 13:22:59 by dmitryzasen       #+#    #+#             */
/*   Updated: 2025/02/12 15:41:19 by dmitryzasen      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int ft_pwd()
{
    char buf[MAXPATHLEN];
    char *dir;

    dir = NULL;
    dir = getcwd(buf, MAXPATHLEN);
    if (!dir)
        return (perror("getcwd"), errno);
    ft_putstr_fd(dir, 1);
    ft_putstr_fd("\n", 1);
    return (SUCCESS);
}
