/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibondarc <ibondarc@student.42vienna.com>   +#+  +:+       +#+        */
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

int			ft_execute(t_app *app);
int			ft_strcmp(char *s1, char *s2);
int			cmd_len(t_cmd *cmd);
int			ft_execute(t_app *app);
int			cmd_len(t_cmd *cmd);
int			token_len(t_token *token);
int			count_types(t_token *token, t_type type);
int			exec_buildin(t_cmd *cmd, t_app *shell, bool is_child, int fd);
int			cd_get_dir(t_cmd *cmd, t_pwd *pwd, t_app *shell, bool is_child);
int			ft_env(char **env);
int			ft_echo(char **args, int fd);
int			ft_cd(t_cmd *cmd, t_app *shell, bool is_child);
int			ft_exit(t_cmd *cmd, t_app *shell, int is_child);
int			close_all_cmnds_fds(t_cmd *cmd);
int			ft_export(t_cmd *cmd, t_app *shell, bool is_child);
int			ft_unset(t_cmd *cmd, t_app *shell, bool is_child);
int			count_redir(t_redir *redir);
int			arr2d_len(char **arr);
int			close_all_redirs_fds(t_redir *redir);
int			access_checking(char *path);
int			readline_event_hook2(void);
int			get_envp_len(t_envp *envp);
int			last_signal_status(void);
int			cd_change_env(t_app *shell, t_pwd *pwd, bool is_child);
int			validate_input_arguments(t_app *shell, t_cmd *cmd, int args_c,
				int is_child);
int			check_export_key(char *str);
int			ft_pwd(void);
int			close_all_redirs_fds_child(t_redir *redir);
int			exe_singl_buildin(t_app *shell, t_cmd *cmd);
int			make_heredoc(t_app *shell);
int			create_heredoc_file(t_app *shell, t_redir *redir);
bool		add_token_back(t_token **token, t_token *new);
bool		is_builtin_func(char *cmd);
bool		lexing_checker(t_app *shell);
bool		handle_command(t_app *shell, t_token *token, char *input, int *i);
bool		handle_operators(t_token *token, char *input, int *i);
bool		handle_heredoc(t_token *prev, char *input, int *i);
bool		validate_file_name(t_token **token, t_redir **redir);
bool		get_type_existence(t_token *token, t_type type);
bool		ft_strstr(char *str, char *to_find);
bool		define_valid_string(char *input);
bool		handle_non_expansion(char **dest, char *input, int *j, int start);
bool		create_new_pwd_node(t_app *shell, char *old_pwd, char *new_pwd);
bool		handle_expansion(char **dest, char *expanded, bool *do_split);
bool		is_there_quote(char *str);
bool		get_pwd(t_app *shell);
bool		create_pwd_env_value(t_app *shell);
bool		create_shell_lvl_env_value(t_app *shell);
bool		create_oldpwd_env_value(t_app *shell);
bool		parse_arguments(t_app *shell, t_cmd *cmd, t_token *token,
				bool *iswriten);
bool		create_pwd_env_value(t_app *shell);
bool		create_oldpwd_env_value(t_app *shell);
void		initialize_shell(t_app *shell, char **envp);
void		free_lib_list(t_lib **lib);
void		show_error_message(char *str);
void		close_file_descriptors(t_cmd *cmd);
void		copy_env(t_app *shell, char **envp);
void		read_input_line(t_app *shell);
void		print_exit_error(char *str, bool is_child);
void		free_2d_array(char **arr);
void		exit_with_error(t_app *shell, int status, char *message);
void		print_child_error(t_app *shell, t_cmd *cmd, char *massage,
				int code);
void		handle_export_showing(char **str, int *i, int *g);
void		free_list(t_app *shell);
bool		get_env_info(t_app *shell);
void		ft_lstadd_back(t_app **shell, t_app *new);
void		create_prompt_path(t_app *shell);
void		sort_2d_env(char **env);
void		add_cmd_back(t_cmd **cmd, t_cmd *new);
void		add_envp_back(t_envp **envp, t_envp *new);
void		handle_signal_main(void);
void		lexing_inputs_data(t_app *shell, char *input);
void		parse_tokens(t_app *shell);
void		free_cmd_list(t_cmd **cmd);
void		free_token_list(t_token **tokens);
void		free_envp_list(t_envp **envp);
void		skip_spases(char *input, int *i);
void		build_env_into_2d_arr(t_app *shell);
void		print_message(char *message, bool flag);
void		unset_env_values(t_app *shell, t_envp **envp);
void		add_redir_back(t_redir **redir, t_redir *new);
void		print_cmd(t_app **shell);
void		skip_quotes(char *input, int *i, char quote);
void		write_value(t_token *token, char *value, int type);
void		skip_all_beafor_variable(char *input, int *j);
void		free_prompt(t_app *shell);
void		handle_child_signal(void);
void		handle_signal_heredoc(void);
void		print_fd_err(char *val, char *err_msg);
void		free_list_in_child(t_app *shell);
void		exit_child(t_app *shell, int status, char *message);
void		change_signal_status(int status);
void		free_redir_list(t_redir **redir);
void		close_fd(int *fd);
void		close_child_fds(t_app *shell);
void		child_process(t_app *shell, t_cmd *cmd);
void		redirects_in_child(t_app *shell, t_cmd *cmd);
void		free_heredoc(t_heredoc *hd);
void		exit_malloc(t_app *shell, bool is_child);
char		*expand_words(t_app *shell, char *input, int *i);
char		*get_word_from_quotes(char *input);
char		**copy_into_2d_arr(t_envp *envp);
char		*find_path(t_app *shell);
char		*divide_into_parts(char *input, int *i);
char		**extract_arguments(t_token *token);
char		*extract_word_from_quotes(char *input);
char		*extract_duble_string(char *input);
char		*extract_word(t_app *shell, char *input, int *i);
char		**create_expanded_args(char *cmd, char *args, int len);
char		*parse_command(t_app *shell, t_cmd *cmd, char *value);
char		**extract_arguments(t_token *token);
char		*execut_subcommand(t_app *shell, char *value);
char		*extract_subcommand(const char *str);
char		*expand_heredoc_input(t_app *shell, char *input);
t_cmd		*create_new_cmd(void);
t_cmd		*last_cmd_node(t_cmd *node);
t_lib		*check_export_arg(char *str, int *exit_code, t_app *shell,
				bool is_child);
t_envp		*create_new_envp(char *envp, char *name);
t_envp		*last_envp_node(t_envp *node);
t_envp		*find_envp_node(t_envp *envp, char *key);
t_token		*create_new_token(void);
t_token		*last_token_node(t_token *node);
t_redir		*create_new_redir(void);
t_redir		*last_redir_node(t_redir *node);
long long	custom_atoi(t_app *shell, t_cmd *cmd, char *arg, int is_child);

#endif
