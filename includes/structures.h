/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibondarc <ibondarc@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 12:39:35 by ibondarc          #+#    #+#             */
/*   Updated: 2025/02/06 12:39:35 by ibondarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURES_H
# define STRUCTURES_H

typedef struct s_lib
{
	char	*key;
	char	*value;
}	t_lib;

typedef struct s_fds
{
	int	prev_pipe;
	int	pipe[2];
	int	dup2_in;
	int	dup2_out;
}	t_fds;

typedef enum s_type
{
	ARG,
	PIPE,
	REDIR_IN,
	REDIR_OUT,
	APPEND,
	HEREDOC,
	ERROR
}	t_type;

typedef struct s_token
{
	t_type			type;
	bool			is_ambiguous;
	char			*err_name;
	char			*value;
	struct s_token	*prev;
	struct s_token	*next;
}	t_token;

typedef struct s_redir
{
	t_type			type;
	char			*value;
	char			*err_name;
	char			*stop_word;
	int				fd;
	bool			is_ambiguous;
	bool			hd_with_quotes;
	struct s_redir	*next;
}	t_redir;

typedef struct s_envp
{
	char			*envp;
	char			*name;
	struct s_envp	*next;
	struct s_envp	*prev;
}	t_envp;

typedef struct s_cmd
{
	int				pipe_fd[2];
	pid_t			pid;
	bool			is_build;
	bool			is_valid_cmd;
	char			*cmd;
	char			**args;
	struct s_redir	*redirs;
	struct s_cmd	*next;
	struct s_cmd	*prev;
}	t_cmd;

typedef struct s_app
{
	char			**env_var;
	char			*user;
	char			*name;
	char			*prompt;
	char			*pwd;
	int				last_exit_code;
	bool			is_valid_syntax;
	bool			is_envp_list_changed;
	int				heredock_num;
	struct s_envp	*envp;
	struct s_cmd	*cmd;
	struct s_token	*tokens;
	struct s_fds	fds;
}	t_app;

typedef struct s_pwd
{
	t_envp	*home;
	t_envp	*oldpwd;
	t_envp	*pwd;
	char	*dir;
	char	*changed_dir;
}	t_pwd;

typedef struct s_heredoc
{
	char	*dest;
	char	*temp;
	int		start;
	int		j;
}	t_heredoc;

typedef struct s_sort_env
{
	t_envp	*curr;
	t_envp	*temp1;
	t_envp	*temp2;
	bool	swapped;
}	t_sort_env;

#endif
