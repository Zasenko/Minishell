#include "../includes/minishell.h"

int main (int ac, char **av, char **env)
{
    (void)av;
    (void)env;
    if (ac > 1)
    {
        char *test = "Hello MiniHell";
        printf("%s\n",test);
        int n = ft_strlen(test);
        printf("\n %d\n", n);
    }
    return 0;
}