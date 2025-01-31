#ifndef MINISHELL_H
# define MINISHELL_H

# include "./libft.h"
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

typedef struct s_app
{
	char			**args;
	char			*input;
	char			*output;
	int				append;
	struct s_app	*next;
    struct s_app    *prev;
}					t_app;

#endif