/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 21:24:27 by marvin            #+#    #+#             */
/*   Updated: 2025/02/07 18:03:26 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "libraries.h"
# include "libft.h"
# include "colors.h"
# include "structures.h"
				
void	initialize_shell(t_app *shell);
void	read_input_line(t_app *shell);
void 	free_allocated_memory(char **arr);
void 	exit_with_error(t_app *shell, int status);
void 	free_list(t_app *shell);
bool 	get_env_info(t_app *shell);
void	ft_lstadd_back(t_app **shell, t_app *new);
bool 	create_prompt_path(t_app *shell);
void	add_node_back(t_cmd **cmd, t_cmd *new);
t_cmd 	*create_new_node(char **args);
t_cmd	*last_node(t_cmd *node);
void    handle_signal(void);

#endif