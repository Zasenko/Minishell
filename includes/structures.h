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

typedef struct s_envp
{
    char            *envp;          //envp variable 
    char            *name;          // envp name
    struct s_envp    *next;          // Next command in pipeline
    struct s_envp    *prev;          // Previous command (doubly linked list)          // First command in pipeline
} t_envp;

typedef struct s_cmd
{
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
    char            *user;          // User name
    char            *name;          // Shell name
    char            *prompt;        // Shell prompt
    char            *pwd;           // Current working directory
    int             last_exit_code; // Stores `$?` value
    struct s_envp   *envp;          // Environment variables
    struct s_cmd    *cmd;           // First command in pipeline
    char            **env;          // env for executor
} t_app;

#endif
