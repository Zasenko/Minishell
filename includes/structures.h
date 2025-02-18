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
    CMD,        // 0
    ARG,        // 1
    PIPE,       // 2
    REDIR_IN,   // 3
    REDIR_OUT,  // 4
    APPEND,     // 5
    HEREDOC,    // 6
    VAR,        // 7
    QUOTE,      // 8
    IN_FILE,    // 9
    OUT_FILE,   // 10
    ERROR       // 11
} t_type;

typedef struct s_token 
{
    t_type          type;
    char            *value;
    struct s_token  *prev;
    struct s_token  *next;
} t_token;

typedef struct s_envp
{
    char            *envp;          //envp variable 
    char            *name;          // envp name
    struct s_envp    *next;          // Next command in pipeline
    struct s_envp    *prev;          // Previous command (doubly linked list)          // First command in pipeline
} t_envp;

typedef struct s_cmd
{
    char            *cmd;
    char            **args;     // Command arguments
    char            *input;     // Input redirection file
    char            *output;    // Output redirection file
    bool            append;     // Append mode for output redirection (`>>`)
    int             fd_in;      // Input file descriptor
    int             fd_out;     // Output file descriptor
    struct s_cmd    *next;      // Next command in pipeline
    struct s_cmd    *prev;      // Previous command (doubly linked list)
    pid_t           pid;        // fork pid id
} t_cmd;

typedef struct s_app
{
    char            **path;         // PATH directories
    char            **env_var;      // envp variable as 2d array
    char            *user;          // User name
    char            *name;          // Shell name
    char            *prompt;        // Shell prompt
    char            *pwd;           // Current working directory
    int             last_exit_code; // Stores `$?` value
    struct s_envp   *envp;          // Environment variables
    struct s_cmd    *cmd;           // First command in pipeline
    struct s_token  *tokens;
    char            **env;          // env for executor
} t_app;

#endif
