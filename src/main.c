#include "../include/pipex.h"
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

void	get_env_path(char *envp[], t_args *args)
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
  ft_printf("error.\ncannot find the PATH var.\n");
}

void	update_cmd_path(t_args *args)
{
	int		 i;

	args->key_values = ft_split(args->env_path, '=');
	args->paths = ft_split(args->key_values[1], ':');
	free_key_values(args);
	i = 0;
	while(args->paths[i++]);
	args->full_paths = (char**)ft_calloc((i), sizeof(char*));
	i = 0;
	while (args->paths[i])
	{
		args->full_paths[i] = ft_strjoin(args->paths[i], "/");
		free(args->paths[i]);
		args->paths[i] = NULL;
		i++;
	}
	free(args->paths);
	args->paths = NULL;
}

void	get_cmd_args_list(char *argv[], t_args *args)
{
	args->cmd1_args = ft_split(argv[2], ' ');
	args->cmd2_args = ft_split(argv[3], ' ');
}

void	get_full_paths_binary(t_args *args, int nth_cmd)
{
	int		i;

	i = 0;
	while (args->full_paths[i++]);
	args->full_paths_binary = (char**)ft_calloc((i), sizeof(char*));
	i = 0;
	while (args->full_paths[i])
	{
		if (nth_cmd == 1)
			args->full_paths_binary[i] = ft_strjoin(args->full_paths[i], args->cmd1_args[0]);
		else
			args->full_paths_binary[i] = ft_strjoin(args->full_paths[i], args->cmd2_args[0]);
		free(args->full_paths[i]);
		args->full_paths[i] = NULL;
		i++;
	}
	free(args->full_paths);
	args->full_paths = NULL;
}

int	check_cmd(char *full_path_binary)
{
	if (access(full_path_binary, F_OK | X_OK) == 0)
		return (1);
	// free_path_binary ?
	return (0);
}

void	run_cmds(t_args *args, int nth_cmd)
{
	int	runnable;
	int	i;

	i = 0;
		while (args->full_paths_binary[i])
		{
			runnable = check_cmd(args->full_paths_binary[i]);
			if (!runnable)
			{
				free_full_paths_binary(i, args->full_paths_binary);
			//	free_everything(args);
			}
			else if (nth_cmd == 1)
				execve(args->full_paths_binary[i], args->cmd1_args, args->envp);
			else
				execve(args->full_paths_binary[i], args->cmd2_args, args->envp);
			i++;
		}
		if (!runnable)
		{
			ft_printf("error. cannot find binary.\n");
			free_full_paths_binary(i, args->full_paths_binary);
			free_everything(args);
		}
}

t_args	*init_args(char *argv[], char *envp[])
{
	t_args	*args;
	args = (t_args *)ft_calloc(1, sizeof(t_args));
	args->envp = envp;
	args->argv = argv;
	get_env_path(envp, args);
	update_cmd_path(args);
	get_cmd_args_list(argv, args);
	args->infile = argv[1];
	args->outfile = argv[4];
	return (args);
}

int	redirect_input(t_args *args)
{
	int fd_in;

	fd_in = open(args->infile, O_RDONLY, 0644);
	if (fd_in == -1)
		return (ft_printf("error: cannot read infile.\n") & 0);
	dup2(fd_in, STDIN_FILENO);
	close(fd_in);
	return (fd_in);
}

int	redirect_output(t_args *args)
{
	int	fd_out;

	fd_out = open(args->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd_out == -1)
		return (ft_printf("error: cannot read outfile.\n") & 0);
	dup2(fd_out, STDOUT_FILENO);
	close(fd_out);
	return (fd_out);
}

int main(int ac, char *argv[], char *envp[])
{
	t_args	*args;
	int		i;
	int		j;
	int		fds[2];
	pid_t	child_one;
	pid_t	child_two;
	int		status;
	pid_t	wpid;

	if (ac < 5)
		return (ft_printf("ac is:%d(need exactly 5.)\n", ac) & 0);
	i = 0;
	j = 0;
	args = init_args(argv, envp);
	pipe(fds);
	child_one = fork();
	if (child_one == 0)
	{
		close(fds[1]);
		close(fds[0]);
		int fd_in = redirect_input(args);	
		dup2(fd_in, STDOUT_FILENO);
		close(fd_in);
		get_full_paths_binary(args, 1);
		run_cmds(args, 1);
	}
	child_two = fork();
	if (child_two == 0)
	{
		//close(fds[0]);
		close(fds[1]);
		int fd_out = redirect_output(args);
		dup2(fd_out, STDIN_FILENO);
		close(fd_out);
		get_full_paths_binary(args, 2);
		run_cmds(args, 2);
	}
	wpid = waitpid(child_one, &status, 0);
	wpid = waitpid(child_two, &status, 0);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	else
		return (-1);
}
