/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   messages.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibondarc <ibondarc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 16:08:03 by ibondarc          #+#    #+#             */
/*   Updated: 2025/04/22 16:08:03 by ibondarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MESSAGES_H
# define MESSAGES_H

# define INVALID_CMD "invalid command!"
# define CMD_NOT_FND ": command not found\n"
# define MALLOC_FAIL "memory allocation failed"
# define FORK_ERROR "fork failed"
# define REDIR_ERROR "redirection failed"
# define PIPE_ERROR "pipe failed"
# define NOT_EXIST "does not exist."
# define QUOTE_ERR "error: there is no right count of quotes"
# define PR "permission denied"
# define SERRNUT_NEWLI "syntax error near unexpected token `newline"
# define SERRNUT "syntax error near unexpected token `"
# define EXIT_TMA "exit: too many arguments\n"
# define EXIT_NAR ": numeric argument required\n"
# define CD_TMA "cd: too many arguments\n"
# define CD_HNS "cd: HOME not set\n"
# define CD_ONS "minishell: cd: OLDPWD not set\n"
# define EXIT "exit\n"

#endif