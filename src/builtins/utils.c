/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmitryzasenko <dmitryzasenko@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 16:15:41 by dmitryzasen       #+#    #+#             */
/*   Updated: 2025/02/12 16:26:44 by dmitryzasen      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_builtin_func(char *cmd)
{
	if (!ft_strncmp("pwd", cmd, ft_strlen(cmd)))
		return (1);
	else
		return (0);
}

int	exec_buildin(t_cmd *cmd)
{
	if (!ft_strncmp("pwd", cmd->args[0], ft_strlen(cmd->args[0])))
		return (ft_pwd());
	return (0);
}
