/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 21:24:27 by marvin            #+#    #+#             */
/*   Updated: 2025/02/05 20:35:18 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include "colors.h"
# include <errno.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/wait.h>
# include <unistd.h>
# include <stdbool.h>

typedef	struct 		s_cmd
{
	char			**args;
	char			*input;
	char			*output;
	int				append;
	struct s_cmd	*next;
    struct s_cmd    *prev;
}					t_cmd;

typedef struct s_app
{
	char			**path;
	char			*user;
	char			*name;
	char			*prompt;
	char			*pwd;
	struct	s_cmd	*cmd;
}					t_app;

void	initialize_shell(t_app *shell);
void	read_input_line(t_app *shell);
void 	free_allocated_memory(char **arr);
void 	exit_with_error(t_app *shell, int status);
void 	free_list(t_app *shell);
bool 	get_env_info(t_app *shell);
void	ft_lstadd_back(t_app **shell, t_app *new);
bool 	create_prompt_path(t_app *shell);



#endif