/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: regillio <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 03:54:11 by regillio          #+#    #+#             */
/*   Updated: 2025/09/18 03:54:18 by regillio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

int	on_wrong_child_pid(t_args *args)
{
	perror("fork");
	close(args->fds[0]);
	close(args->fds[1]);
	free_everything(args);
	free(args);
	return (0);
}

void	execute_first_child(t_args *args)
{
	close(args->fds[0]);
	if (redirect_input(args) == 0)
	{
		free_everything(args);
		clean_struct(args);
		exit(EXIT_FAILURE);
	}
	if (dup2(args->fds[1], STDOUT_FILENO) == -1)
	{
		perror("dup2");
		close(args->fds[1]);
		free_everything(args);
		clean_struct(args);
		exit(EXIT_FAILURE);
	}
	close(args->fds[1]);
	get_full_paths_binary(args, 1);
	run_cmds(args, 1);
}

void	execute_second_child(t_args *args)
{
	close(args->fds[1]);
	if (dup2(args->fds[0], STDIN_FILENO) == -1)
	{
		perror("dup2 child2");
		close(args->fds[0]);
		free_everything(args);
		clean_struct(args);
		exit(EXIT_FAILURE);
	}
	close(args->fds[0]);
	if (redirect_output(args) == 0)
	{
		free_everything(args);
		clean_struct(args);
		exit(EXIT_FAILURE);
	}
	get_full_paths_binary(args, 2);
	run_cmds(args, 2);
}

void	wait_children(t_args *args)
{
	waitpid(args->child_one, &args->status, 0);
	waitpid(args->child_two, &args->status, 0);
	if (WIFEXITED(args->status))
		args->exit_status = WEXITSTATUS(args->status);
	else
		args->exit_status = -1;
}
