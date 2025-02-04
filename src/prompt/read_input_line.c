#include "../../includes/minishell.h"

char *create_prompt_path(t_app *shell)
{
    char    *prompt;
    char    *temp;
    int     i;

    prompt = ft_strjoin(GREEN, shell->name);
    if (!prompt) 
        return NULL;
    i = 0;
    char    *parts[] = {"@", shell->user, RESET, ":", BLUE, shell->pwd, RESET, "$ "};
    while ( i < 8) 
    {
        temp = ft_strjoin(prompt, parts[i]);
        free(prompt);
        if (!temp)
            return NULL;
        prompt = temp;
        i++;
    }
    return prompt;
}

void read_input_line(t_app *shell)
{
    char *input;
    char *prompt;

    while (1) 
    {
        prompt = create_prompt_path(shell);
        if (!prompt)
            break ;
        input = readline(prompt);
        if (!input) 
        {
            printf("exit\n");
            break;
        }
        if (*input)
            add_history(input);
        printf("%s\n", input);
        // in this place you can do pars and so on!!
    }
}