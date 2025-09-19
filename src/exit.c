/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: regillio <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 03:54:29 by regillio          #+#    #+#             */
/*   Updated: 2025/09/18 03:54:30 by regillio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"
#include <asm-generic/errno-base.h>
#include <unistd.h>

void	print_error_message(char *cmd_name, char *msg)
{
	write(STDERR_FILENO, "pipex: ", 7);
	if (cmd_name && *cmd_name)
	{
		write(STDERR_FILENO, msg, ft_strlen(msg));
		write(STDERR_FILENO, ": ", 2);
		write(STDERR_FILENO, cmd_name, ft_strlen(cmd_name));
	}
	else
	{
		write(STDERR_FILENO, ": ", 2);
		write(STDERR_FILENO, msg, ft_strlen(msg));
	}
	write(STDERR_FILENO, "\n", 1);
}

void	exit_on_cmd_list(t_args *args, char *cmd_name)
{
	print_error_message(cmd_name, "command not found");
	free_full_paths_binary(&args->full_paths_binary);
	free_everything(args);
	clean_struct(args);
	exit(127);
}

void	exit_on_cmd_path(t_args *args, char *cmd_name)
{
	print_error_message(cmd_name, "command not found");
	free_everything(args);
	clean_struct(args);
	exit(127);
}

void	exit_on_binary(t_args *args, char *cmd_name)
{
	int	err_no;
	int	exit_code;

	err_no = errno;
	if (err_no == 0)
		err_no = ENOENT;
	if (err_no == ENOENT)
	{
		print_error_message(cmd_name, "command not found");
		exit_code = 127;
	}
	else if (err_no == EACCES)
	{
		print_error_message(cmd_name, "Permission denied");
		exit_code = 126;
	}
	else
	{
		print_error_message(cmd_name, strerror(err_no));
		exit_code = 126;
	}
	free_full_paths_binary(&args->full_paths_binary);
	free_everything(args);
	clean_struct(args);
	exit(exit_code);
}

void	close_fds(t_args *args)
{
	close(args->fds[0]);
	close(args->fds[1]);
}
