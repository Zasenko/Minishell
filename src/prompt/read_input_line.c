#include "../../includes/minishell.h"

void read_input_line(t_app *shell)
{
    char *input;

    if (!create_prompt_path(shell))
        exit_with_error(shell, 1);
    while (1) 
    {
        input = readline(shell->prompt);
        if (!input) 
            break ;
        if (*input)
        {
            add_history(input);
            printf("%s\n", input);
            break ;
        // in this place you can do pars and so on!!
        }
    }
    exit_with_error(shell, 1);
}