/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_input_line.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibondarc <ibondarc@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 12:29:00 by ibondarc          #+#    #+#             */
/*   Updated: 2025/02/12 12:29:00 by ibondarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	read_input_line(t_app *shell)
{
	char	*input;

	if (!shell)
		return ;
	while (1)
	{
		handle_signal_main();
		build_env_into_2d_arr(shell);
		create_prompt_path(shell);
		input = readline(shell->prompt);
		if (last_signal_status() == 2)
			shell->last_exit_code = 130;
		if (input == NULL)
			break ;
		add_history(input);
		lexing_inputs_data(shell, input);
		parse_tokens(shell);
		ft_execute(shell);
		close_child_fds(shell);
		close_fd(&shell->fds.dup2_in);
		close_fd(&shell->fds.dup2_out);
		free_list(shell);
	}
	printf("exit\n");
	exit_with_error(shell, shell->last_exit_code, NULL);
}
