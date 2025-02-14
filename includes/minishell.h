/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 21:24:27 by marvin            #+#    #+#             */
/*   Updated: 2025/02/10 16:09:25 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "libraries.h"
# include "libft.h"
# include "colors.h"
# include "structures.h"
				
void	initialize_shell(t_app *shell, char **envp);
void    copy_env(t_app *shell, char **envp);
void	read_input_line(t_app *shell);
void 	free_2d_array(char **arr);
void 	exit_with_error(t_app *shell, int status);
void 	free_list(t_app *shell);
bool 	get_env_info(t_app *shell);
void	ft_lstadd_back(t_app **shell, t_app *new);
bool 	create_prompt_path(t_app *shell);
void	add_cmd_back(t_cmd **cmd, t_cmd *new);
t_cmd 	*create_new_cmd(void);
t_cmd	*last_cmd_node(t_cmd *node);
void	add_envp_back(t_envp **envp, t_envp *new);
t_envp 	*create_new_envp(char *envp, char *name);
t_envp	*last_envp_node(t_envp *node);
void	add_token_back(t_token **token, t_token *new);
t_token *create_new_token(char *value, t_type type);
int	    token_len(t_token *token);
t_token *last_token_node(t_token *node);
void    handle_signal(void);
int     ft_execute(t_app *app);
int	    cmd_len(t_cmd *cmd);
bool    lexing_inputs_data(t_app *shell, char *input);
bool    parse_tokens(t_app *shell);

#endif