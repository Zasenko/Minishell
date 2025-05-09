/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibondarc <ibondarc@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 13:01:47 by ibondarc          #+#    #+#             */
/*   Updated: 2025/05/09 13:02:52 by ibondarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	print_fd_err(char *val, char *err_msg)
{
	char	*err[4];
	char	*temp;
	char	*res;
	int		i;

	if (!val || !err_msg)
		return ;
	i = 0;
	err[0] = val;
	err[1] = ": ";
	err[2] = err_msg;
	err[3] = "\n";
	res = ft_strdup("");
	while (i < 4)
	{
		temp = ft_strjoin(res, err[i]);
		free(res);
		if (!temp)
			return ;
		res = temp;
		i++;
	}
	ft_putstr_fd(res, 2);
	free(res);
}

void	print_child_error(t_app *shell, t_cmd *cmd, char *massage, int code)
{
	char	*error_msg;

	error_msg = ft_strjoin(cmd->args[0], massage);
	if (!error_msg)
		exit_child(shell, 1, NULL);
	ft_putstr_fd(error_msg, 2);
	free(error_msg);
	exit_child(shell, code, NULL);
}
