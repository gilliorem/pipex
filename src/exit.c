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

void	exit_on_cmd_list(t_args *args)
{
	ft_printf("error. empty cmd.\n");
	free_full_paths_binary(&args->full_paths_binary);
	free_everything(args);
	clean_struct(args);
	exit(EXIT_FAILURE);
}

void	exit_on_cmd_path(t_args *args)
{
	ft_printf("error. no cmd path.\n");
	free_everything(args);
	clean_struct(args);
	exit(EXIT_FAILURE);
}

void	exit_on_binary(t_args *args)
{
	ft_printf("error. cannot find binary.\n");
	free_full_paths_binary(&args->full_paths_binary);
	free_everything(args);
	clean_struct(args);
	exit(EXIT_FAILURE);
}

void	close_fds(t_args *args)
{
	close(args->fds[0]);
	close(args->fds[1]);
}
