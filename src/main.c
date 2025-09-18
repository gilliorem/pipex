#include "../include/pipex.h"
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

void    get_env_path(char *envp[], t_args *args)
{
    int i;

    i = 0;
    while (envp[i])
    {
        if (ft_strncmp("PATH=", envp[i], 5) == 0)
        {
            args->env_path = envp[i];
            return ;
        }
        i++;
    }
    ft_putendl_fd("error.", STDERR_FILENO);
    ft_putendl_fd("cannot find the PATH var.", STDERR_FILENO);
}

int     update_cmd_path(t_args *args)
{
    int i;

    if (!args->env_path)
        return (-1);
    args->key_values = ft_split(args->env_path, '=');
    if (!args->key_values || !args->key_values[1])
    {
        free_key_values(args);
        return (-1);
    }
    args->paths = ft_split(args->key_values[1], ':');
    free_key_values(args);
    if (!args->paths)
        return (-1);
    i = 0;
    while (args->paths[i])
        i++;
    args->full_paths = (char **)ft_calloc(i + 1, sizeof(char *));
    if (!args->full_paths)
        return (-1);
    i = 0;
    while (args->paths[i])
    {
        args->full_paths[i] = ft_strjoin(args->paths[i], "/");
        if (!args->full_paths[i])
            return (-1);
        i++;
    }
    free_paths(args);
    return (0);
}

void    get_cmd_args_list(char *argv[], t_args *args)
{
    args->cmd1_args = ft_split(argv[2], ' ');
    args->cmd2_args = ft_split(argv[3], ' ');
}

void    get_full_paths_binary(t_args *args, int nth_cmd)
{
    int     i;
    int     count;
    char    **cmd_args;

    if (!args->full_paths)
        return ;
    cmd_args = args->cmd1_args;
    if (nth_cmd == 2)
        cmd_args = args->cmd2_args;
    if (!cmd_args || !cmd_args[0])
        return ;
    count = 0;
    while (args->full_paths[count])
        count++;
    args->full_paths_binary = (char **)ft_calloc(count + 1, sizeof(char *));
    if (!args->full_paths_binary)
        return ;
    i = 0;
    while (i < count)
    {
        args->full_paths_binary[i] = ft_strjoin(args->full_paths[i], cmd_args[0]);
        if (!args->full_paths_binary[i])
        {
            free_full_paths_binary(&args->full_paths_binary);
            break ;
        }
        i++;
    }
    i = 0;
    while (args->full_paths[i])
    {
        free(args->full_paths[i]);
        args->full_paths[i] = NULL;
        i++;
    }
    free(args->full_paths);
    args->full_paths = NULL;
}

int     check_cmd(char *full_path_binary)
{
    if (access(full_path_binary, F_OK | X_OK) == 0)
        return (1);
    return (0);
}

void    run_cmds(t_args *args, int nth_cmd)
{
    int i;

    if (!args->full_paths_binary)
    {
        ft_putendl_fd("error. cannot find binary.", STDERR_FILENO);
        clean_struct(args);
        exit(127);
    }
    i = 0;
    while (args->full_paths_binary[i])
    {
        if (check_cmd(args->full_paths_binary[i]))
        {
            if (nth_cmd == 1)
                execve(args->full_paths_binary[i], args->cmd1_args, args->envp);
            else
                execve(args->full_paths_binary[i], args->cmd2_args, args->envp);
            perror("execve");
        }
        i++;
    }
    ft_putendl_fd("error. cannot find binary.", STDERR_FILENO);
    clean_struct(args);
    exit(127);
}

t_args  *init_args(char *argv[], char *envp[])
{
    t_args  *args;

    args = (t_args *)ft_calloc(1, sizeof(t_args));
    if (!args)
        return (NULL);
    args->envp = envp;
    args->argv = argv;
    get_env_path(envp, args);
    if (!args->env_path)
    {
        clean_struct(args);
        return (NULL);
    }
    if (update_cmd_path(args) == -1)
    {
        clean_struct(args);
        return (NULL);
    }
    get_cmd_args_list(argv, args);
    if (!args->cmd1_args || !args->cmd2_args || !args->cmd1_args[0] || !args->cmd2_args[0])
    {
        clean_struct(args);
        return (NULL);
    }
    args->infile = argv[1];
    args->outfile = argv[4];
    return (args);
}

int     redirect_input(t_args *args)
{
    int fd_in;

    fd_in = open(args->infile, O_RDONLY);
    if (fd_in == -1)
    {
        ft_putendl_fd("error: cannot read infile.", STDERR_FILENO);
        return (-1);
    }
    if (dup2(fd_in, STDIN_FILENO) == -1)
    {
        perror("dup2");
        close(fd_in);
        return (-1);
    }
    close(fd_in);
    return (0);
}

int     redirect_output(t_args *args)
{
    int fd_out;

    fd_out = open(args->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd_out == -1)
    {
        ft_putendl_fd("error: cannot read outfile.", STDERR_FILENO);
        return (-1);
    }
    if (dup2(fd_out, STDOUT_FILENO) == -1)
    {
        perror("dup2");
        close(fd_out);
        return (-1);
    }
    close(fd_out);
    return (0);
}

static void execute_first_child(t_args *args, int fds[2])
{
    close(fds[0]);
    if (redirect_input(args) == -1)
    {
        clean_struct(args);
        exit(EXIT_FAILURE);
    }
    if (dup2(fds[1], STDOUT_FILENO) == -1)
    {
        perror("dup2");
        close(fds[1]);
        clean_struct(args);
        exit(EXIT_FAILURE);
    }
    close(fds[1]);
    get_full_paths_binary(args, 1);
    run_cmds(args, 1);
}

static void execute_second_child(t_args *args, int fds[2])
{
    close(fds[1]);
    if (dup2(fds[0], STDIN_FILENO) == -1)
    {
        perror("dup2");
        close(fds[0]);
        clean_struct(args);
        exit(EXIT_FAILURE);
    }
    close(fds[0]);
    if (redirect_output(args) == -1)
    {
        clean_struct(args);
        exit(EXIT_FAILURE);
    }
    get_full_paths_binary(args, 2);
    run_cmds(args, 2);
}

int main(int ac, char *argv[], char *envp[])
{
    t_args  *args;
    int     fds[2];
    pid_t   child_one;
    pid_t   child_two;
    int     status2;

    if (ac != 5)
    {
        ft_putstr_fd("ac is:", STDERR_FILENO);
        ft_putnbr_fd(ac, STDERR_FILENO);
        ft_putendl_fd(" (need exactly 5.)", STDERR_FILENO);
        return (1);
    }
    args = init_args(argv, envp);
    if (!args)
        return (1);
    if (pipe(fds) == -1)
    {
        perror("pipe");
        clean_struct(args);
        return (1);
    }
    child_one = fork();
    if (child_one == -1)
    {
        perror("fork");
        close(fds[0]);
        close(fds[1]);
        clean_struct(args);
        return (1);
    }
    if (child_one == 0)
        execute_first_child(args, fds);
    child_two = fork();
    if (child_two == -1)
    {
        perror("fork");
        close(fds[0]);
        close(fds[1]);
        waitpid(child_one, NULL, 0);
        clean_struct(args);
        return (1);
    }
    if (child_two == 0)
        execute_second_child(args, fds);
    close(fds[0]);
    close(fds[1]);
    waitpid(child_one, NULL, 0);
    waitpid(child_two, &status2, 0);
    clean_struct(args);
    if (WIFEXITED(status2))
        return (WEXITSTATUS(status2));
    return (1);
}
