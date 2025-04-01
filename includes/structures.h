/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 12:39:35 by marvin            #+#    #+#             */
/*   Updated: 2025/02/06 12:39:35 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

typedef enum
{
    ARG,        // 1
    PIPE,       // 2
    REDIR_IN,   // 3
    REDIR_OUT,  // 4
    APPEND,     // 5
    HEREDOC,    // 6
    ERROR       // 11
} t_type;

typedef struct s_token 
{
    t_type          type;
    char            *value;
    struct s_token  *prev;
    struct s_token  *next;
} t_token;

typedef struct s_redir 
{
    t_type          type;
    char            *value;
    char            *stop_word; //For HEREDOCK
    int             fd;
    bool             heredock_with_quotes;
    struct s_redir  *next;
} t_redir;

typedef struct s_envp
{
    char            *envp;          //envp variable 
    char            *name;          // envp name
    struct s_envp    *next;          // Next command in pipeline
    struct s_envp    *prev;          // Previous command (doubly linked list)          
} t_envp;

typedef struct s_cmd
{
    char            *cmd;
    char            **args;     // Command arguments
    bool            is_build;
    bool            is_valid_cmd;
    struct s_redir  *redirs;
    struct s_cmd    *next;      // Next command in pipeline
    struct s_cmd    *prev;      // Previous command (doubly linked list)
    pid_t           pid;        // fork pid id
} t_cmd;

typedef struct s_app
{
    char            **env_var;      // envp variable as 2d array
    char            *user;          // User name
    char            *name;          // Shell name
    char            *prompt;        // Shell prompt
    char            *pwd;           // Current working directory
    int             last_exit_code; // Stores `$?` value
    struct s_envp   *envp;          // Environment variables
    bool            is_envp_list_changed; //FLAG if we need to make new char** env_var
    struct s_cmd    *cmd;           // First command in pipeline
    struct s_token  *tokens;
    bool            is_valid_syntax;
    int             heredock_num;
} t_app;

#endif
