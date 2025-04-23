/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibondarc <ibondarc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 21:24:41 by ibondarc          #+#    #+#             */
/*   Updated: 2025/02/10 18:02:51 by ibondarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_app	shell;

	(void)argc;
	(void)argv;
	initialize_shell(&shell, envp);
	handle_signal_main();
	read_input_line(&shell);
	return (0);
}
