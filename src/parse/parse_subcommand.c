// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   execut_subcommand.c                                :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2025/02/23 17:10:11 by marvin            #+#    #+#             */
// /*   Updated: 2025/02/23 17:10:11 by marvin           ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

// #include "../../includes/minishell.h"

// char *parent_subprocess(t_app *shell, pid_t pid, int *fd)
// {   
//     int status;
//     char buffer[1024];
//     ssize_t b;

//     close(fd[1]);
//     b = read(fd[0], buffer, sizeof(buffer));
//     if (b == -1)
//         printf("read error\n");
//     buffer[b - 1] = '\0';
//     close(fd[0]);
//     waitpid(pid, &status, 0);
//     shell->last_exit_code = WEXITSTATUS(status);
//     return (ft_strdup(buffer));
// }
// void child_subprocess(t_app *shell, int *fd, char *value)
// {
//     char    *cmd;
//     char    **args;

//     close(fd[0]);
//     dup2(fd[1], STDOUT_FILENO);
//     close(fd[1]);
//     cmd = parse_command(shell, value);
//     if (!cmd)
//     {
// 		exit_with_error(shell, CICE, CMD_NOT_FND);
//     }
//     args = create_expanded_args(value, value, 1);
//     if (!args)
//     {
//         free(cmd);
// 		exit_with_error(shell, errno, CMD_NOT_FND);
//     }
//     execve(cmd, args, shell->env_var);
//     exit_with_error(shell, errno, NULL);
// }
// char    *execut_subcommand(t_app *shell, char *value)
// {
//     char    *res = NULL;
//     pid_t   pid;
//     int     fd[2];

//     res = NULL;
//     pipe(fd); 
//     pid = fork();
//     if (pid == -1)
//         return NULL;
//     if (pid == 0) 
//         child_subprocess(shell, fd, value);
//     else
//         res = parent_subprocess(shell, pid, fd);
//     if (!res)
//         return NULL;
//     return  (res);
// }