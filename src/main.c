/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: regillio <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 03:54:50 by regillio          #+#    #+#             */
/*   Updated: 2025/09/18 03:54:51 by regillio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

t_args	*init_args(char *argv[], char *envp[])
{
	t_args	*args;

	args = (t_args *)ft_calloc(1, sizeof(t_args));
	if (!args)
		return (NULL);
	args->envp = envp;
	args->argv = argv;
	get_env_path(envp, args);
	update_cmd_path(args);
	get_cmd_args_list(argv, args);
	args->infile = argv[1];
	args->outfile = argv[4];
	return (args);
}

void	run_cmds(t_args *args, int nth_cmd)
{
	char	**cmd_args;
	int		i;

	i = 0;
	cmd_args = args->cmd1_args;
	if (nth_cmd == 2)
		cmd_args = args->cmd2_args;
	if (!cmd_args || !cmd_args[0])
		exit_on_cmd_list(args);
	if (!args->full_paths_binary)
		exit_on_cmd_path(args);
	while (args->full_paths_binary[i])
	{
		if (access(args->full_paths_binary[i], F_OK | X_OK) == 0)
			execve(args->full_paths_binary[i], cmd_args, args->envp);
		i++;
	}
	exit_on_binary(args);
}

int	pipe_check(t_args *args)
{
	if (pipe(args->fds) == -1)
	{
		perror("pipe");
		free_everything(args);
		free(args);
		return (0);
	}
	return (0);
}

int	main(int ac, char *argv[], char *envp[])
{
	t_args	*args;
	int		exit_status;

	if (ac != 5)
		return (ft_printf("ac is:%d(need exactly 5.)\n", ac) & 0);
	args = init_args(argv, envp);
	pipe_check(args);
	args->child_one = fork();
	if (args->child_one == -1)
		return (on_wrong_child_pid(args));
	if (args->child_one == 0)
		execute_first_child(args);
	args->child_two = fork();
	if (args->child_two == -1)
		return (on_wrong_child_pid(args));
	if (args->child_two == 0)
		execute_second_child(args);
	close_fds(args);
	wait_children(args);
	exit_status = args->exit_status;
	clean_up(args);
	return (exit_status);
}
