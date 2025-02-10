#include "../../includes/minishell.h"

// A simple example of parsing cmd  
void parse_args(t_app *shell, char *args)
{
    char **res = ft_split(args, ' ');
    if (!res)
        return ;
    add_cmd_back(&shell->cmd, create_new_cmd(res));
}

void read_input_line(t_app *shell)
{
    char *input;

    if (!shell)
        return ;
    if (!create_prompt_path(shell))
        exit_with_error(shell, 1);
    while (1) 
    {
        input = readline(shell->prompt);
        if (!input)
            exit_with_error(shell, 1);
        if (*input)
        {
            add_history(input);
            // in this place you can do a pars of comannd!!
            parse_args(shell, input);
        }
    }
}