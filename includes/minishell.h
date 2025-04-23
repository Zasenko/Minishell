/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibondarc <ibondarc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 21:24:27 by ibondarc          #+#    #+#             */
/*   Updated: 2025/02/18 11:37:29 by ibondarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "colors.h"
# include "exit_status.h"
# include "libft.h"
# include "libraries.h"
# include "messages.h"
# include "structures.h"

void	initialize_shell(t_app *shell, char **envp);
void	copy_env(t_app *shell, char **envp);
void	read_input_line(t_app *shell);
void	free_2d_array(char **arr);
void	exit_with_error(t_app *shell, int status, char *message);
void	free_list(t_app *shell);
bool	get_env_info(t_app *shell);
void	ft_lstadd_back(t_app **shell, t_app *new);
void	create_prompt_path(t_app *shell);
void	add_cmd_back(t_cmd **cmd, t_cmd *new);
t_cmd	*create_new_cmd(void);
t_cmd	*last_cmd_node(t_cmd *node);
void	add_envp_back(t_envp **envp, t_envp *new);
t_envp	*create_new_envp(char *envp, char *name);
t_envp	*last_envp_node(t_envp *node);
bool	add_token_back(t_token **token, t_token *new);
t_token *create_new_token(void);
int	    token_len(t_token *token);
t_token *last_token_node(t_token *node);
void    handle_signal_main(void);
int     ft_execute(t_app *app);
int	    cmd_len(t_cmd *cmd);
void    lexing_inputs_data(t_app *shell, char *input);
void    parse_tokens(t_app *shell);
char    *parse_command(t_app *shell, t_cmd *cmd, char *value);
int     count_types(t_token *token, t_type type);
void    free_cmd_list(t_cmd **cmd);
void    free_token_list(t_token **tokens);
void    free_envp_list(t_envp **envp);
bool	is_builtin_func(char *cmd);
int	exec_buildin(t_cmd *cmd, t_app *shell, bool is_child, int fd);
int	ft_pwd(void);
bool	lexing_checker(t_app *shell);
bool	handle_command(t_app *shell, t_token *token, char *input, int *i);
bool	handle_operators(t_token *token, char *input, int *i);
bool	handle_variable(t_app *shell, t_token *token, t_token *prev,
		char *input, int *i);
char	*extract_duble_string(char *input);
bool	handle_heredoc(t_token *prev, char *input, int *i);
char	*extract_word(t_app *shell, char *input, int *i);
void	skip_spases(char *input, int *i);
bool	get_type_existence(t_token *token, t_type type);
int	get_envp_len(t_envp *envp);
void	build_env_into_2d_arr(t_app *shell);
void	print_message(char *message, bool flag);
void	unset_env_values(t_app *shell, t_envp **envp);
int	ft_env(char **env);
int	ft_echo(char **args, int fd);
int	ft_cd(t_cmd *cmd, t_app *shell, bool is_child);
bool	ft_strstr(char *str, char *to_find);
char	**create_expanded_args(char *cmd, char *args, int len);
char	**extract_arguments(t_token *token);
char	*execut_subcommand(t_app *shell, char *value);
char	*extract_subcommand(const char *str);
int	ft_exit(t_cmd *cmd, t_app *shell, int is_child);
int	close_all_cmnds_fds(t_cmd *cmd);
bool	define_valid_string(char *input);
int	ft_export(t_cmd *cmd, t_app *shell, bool is_child);
t_envp	*find_envp_node(t_envp *envp, char *key);
int	ft_unset(t_cmd *cmd, t_app *shell, bool is_child);
t_redir	*create_new_redir(void);
t_redir	*last_redir_node(t_redir *node);
void	add_redir_back(t_redir **redir, t_redir *new);
int	count_redir(t_redir *redir);
int	arr2d_len(char **arr);
int	close_all_redirs_fds(t_redir *redir);
void	print_cmd(t_app **shell);
char	*expand_words(t_app *shell, char *input, int *i);
void	skip_quotes(char *input, int *i, char quote);
char	*get_word_from_quotes(char *input);
int	access_checking(char *path);
char	**copy_into_2d_arr(t_envp *envp);
char *find_path(t_app *shell);
void	write_value(t_token *token, char *value, int type);
char	*divide_into_parts(char *input, int *i);
void	skip_all_beafor_variable(char *input, int *j);
bool	handle_non_expansion(char **dest, char *input, int *j, int start);
bool	handle_expansion(char **dest, char *expanded, bool *do_split);
char	**extract_arguments(t_token *token);
bool	is_there_quote(char *str);
char	*extract_word_from_quotes(char *input);
bool	parse_arguments(t_app *shell, t_cmd *cmd, t_token *token,
		bool *iswriten);
void	free_prompt(t_app *shell);
int last_signal_status(void);
void handle_child_signal(void);
void handle_signal_heredoc(void);
int readline_event_hook2(void);
void print_fd_err(char *val, char *err_msg);
int	cd_change_env(t_app *shell, t_pwd *pwd, char *current_dir, bool is_child);
void free_list_in_child(t_app *shell);
void	exit_child(t_app *shell, int status, char *message);
void		free_redir_list(t_redir **redir);
#endif