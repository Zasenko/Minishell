#include "../../includes/minishell.h"

int cmds_len(t_cmd *cmd)
{
    t_cmd *temp;
    int i;

    i = 0;
    temp = cmd;
    if (!temp)
        return i;
    while (temp != NULL)
    {
        i++;
        temp = temp->next;
    }
    return i;
}

int close_all_cmnds_fds(t_cmd *cmd)
{
    t_cmd *temp;

    temp = cmd;
    if (!temp)
        return 0;
    while (temp != NULL)
    {
        if (temp->fd_in != -1)
        {
            close(temp->fd_in);
        }
        if (temp->fd_out != -1)
        {
            close(temp->fd_out);
        }
        temp = temp->next;
    }
    return 1;
}

void child_process(t_app *app, t_cmd *cmd, int prev_pipe, int pipe_fd[2])
{
    if (prev_pipe != -1)
    {
        dup2(prev_pipe, 0);
        close(prev_pipe);
    }
    if (cmd->fd_in != -1)
        dup2(cmd->fd_in, 0);

    if (cmd->fd_out != -1)
        dup2(cmd->fd_out, 1);
    if (cmd->next != NULL)
    {
        dup2(pipe_fd[1], 1);
    }
    if (pipe_fd[0] != -1)
        close(pipe_fd[0]);
    if (pipe_fd[1] != -1)
        close(pipe_fd[1]);
    close_all_cmnds_fds(app->cmd);
    if (execve(cmd->args[0], cmd->args, app->env) != 0)
    {
        perror("execve");
        exit(EXIT_FAILURE);
    }
}

int ft_execute_command(t_app *app, t_cmd *cmd, int *prev_pipe)
{
    int pipe_fd[2];

    pipe_fd[0] = -1;
    pipe_fd[1] = -1;
    if (cmd->next != NULL)
    {
        if (pipe(pipe_fd) != 0)
        {
            // check
            perror("pipe");
            return (0); // todo? break and waitpid?
        }
    }
    cmd->pid = fork();
    if (cmd->pid < 0)
    {
        perror("fork");
        return (0); // todo? break and waitpid?
    }
    // child
    if (cmd->pid == 0)
        child_process(app, cmd, *prev_pipe, pipe_fd);

    if (*prev_pipe != -1)
        close(*prev_pipe);
    if (pipe_fd[1] != -1)
        close(pipe_fd[1]);
    *prev_pipe = pipe_fd[0];
    return (1);
}

int ft_execute(t_app *app)
{
    t_cmd *cmd;
    int cmd_count;
    int prev_pipe;

    cmd = app->cmd;
    cmd_count = cmds_len(cmd);
    prev_pipe = -1;
    if (!cmd_count)
        return 0;
    while (cmd != NULL)
    {
        ft_execute_command(app, cmd, &prev_pipe);
        cmd = cmd->next;
    }
    // waitpid
    cmd = app->cmd;
    while (cmd != NULL)
    {
        if (cmd->pid != -1)
        {
            waitpid(cmd->pid, NULL, 0);
        }
        cmd = cmd->next;
    }
    return 1;
}

// int main(int ac, char **av, char **env)
// {

//     (void)ac;
//     (void)av;

//     t_cmd *cmd1 = malloc(sizeof(t_cmd));
//     cmd1->args = (char *[]){"/bin/cat", NULL};
//     cmd1->input = NULL;
//     cmd1->output = NULL;
//     cmd1->append = false;
//     cmd1->fd_in = open("executor.c", O_RDONLY);
//     cmd1->fd_out = -1;
//     cmd1->next = NULL;
//     cmd1->prev = NULL;

//     t_cmd *cmd2 = malloc(sizeof(t_cmd));
//     cmd2->args = (char *[]){"/usr/bin/wc", "-c", NULL};
//     cmd2->input = NULL;
//     cmd2->output = NULL;
//     cmd2->append = false;
//     cmd2->fd_in = -1;
//     cmd2->fd_out = open("test_cmd2.txt", O_CREAT | O_RDWR);
//     cmd2->next = NULL;
//     cmd2->prev = NULL;

//     t_cmd *cmd3 = malloc(sizeof(t_cmd));
//     cmd3->args = (char *[]){"/bin/cat", "-e", NULL};
//     cmd3->input = NULL;
//     cmd3->output = NULL;
//     cmd3->append = false;
//     cmd3->fd_in = -1;
//     cmd3->fd_out = -1;
//     cmd3->next = NULL;
//     cmd3->prev = NULL;

//     t_cmd *cmd4 = malloc(sizeof(t_cmd));
//     cmd4->args = (char *[]){"/usr/bin/wc", "-c", NULL};
//     cmd4->input = NULL;
//     cmd4->output = NULL;
//     cmd4->append = false;
//     cmd4->fd_in = -1;
//     cmd4->fd_out = open("test_cmd4.txt", O_CREAT | O_RDWR);
//     cmd4->next = NULL;
//     cmd4->prev = NULL;

//     cmd1->next = cmd2;
//     cmd2->next = cmd3;
//     cmd3->next = cmd4;

//     t_app app;
//     app.cmd = cmd1;
//     app.env = env;

//     // Выполнение пайплайна
//     if (!ft_execute(&app))
//     {
//         perror("Execution failed");
//     }

//     close_all_cmnds_fds(app.cmd);
//     // Освобождение памяти
//     free(cmd1);
//     free(cmd2);
//     free(cmd3);
//     free(cmd4);
//     return 0;
// }