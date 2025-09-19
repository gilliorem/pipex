/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: regillio <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 03:54:33 by regillio          #+#    #+#             */
/*   Updated: 2025/09/18 03:54:35 by regillio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	free_key_values(t_args *args)
{
	free_string_array(&args->key_values);
}

void	free_paths(t_args *args)
{
	free_string_array(&args->paths);
}

void	free_cmd_args(char ***cmd_args)
{
	free_string_array(cmd_args);
}

void	free_full_paths(t_args *args)
{
	free_string_array(&args->full_paths);
}

void	free_full_paths_binary(char ***full_paths_binary)
{
	free_string_array(full_paths_binary);
}
