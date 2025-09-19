/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_up.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: regillio <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 03:54:22 by regillio          #+#    #+#             */
/*   Updated: 2025/09/18 03:54:24 by regillio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	free_string_array(char ***array)
{
	int	i;

	i = 0;
	if (!array || !*array)
		return ;
	while ((*array)[i])
	{
		free((*array)[i]);
		(*array)[i] = NULL;
		i++;
	}
	free(*array);
	(*array) = NULL;
}

void	free_everything(t_args *args)
{
	if (!args)
		return ;
	free_key_values(args);
	free_paths(args);
	free_cmd_args(&args->cmd1_args);
	free_cmd_args(&args->cmd2_args);
	free_full_paths(args);
}

void	clean_struct(t_args *args)
{
	if (!args)
		return ;
	free_full_paths_binary(&args->full_paths_binary);
	free(args);
}

void	clean_up(t_args *args)
{
	free_everything(args);
	free(args);
	args = NULL;
}
