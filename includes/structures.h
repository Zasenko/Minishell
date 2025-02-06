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
} t_cmd;

typedef struct s_app
{
    char            **path;         // PATH directories
    char            *user;          // User name
    char            *name;          // Shell name
    char            *prompt;        // Shell prompt
    char            *pwd;           // Current working directory
    char            **envp;         // Environment variables
    int             last_exit_code; // Stores `$?` value
    struct s_cmd    *cmd;           // First command in pipeline
} t_app;

#endif
