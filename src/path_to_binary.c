/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_to_binary.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: regillio <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 03:54:56 by regillio          #+#    #+#             */
/*   Updated: 2025/09/18 03:54:57 by regillio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	get_env_path(char *envp[], t_args *args)
{
	int	i;

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
	args->env_path = NULL;
	ft_printf("error.\ncannot find the PATH var.\n");
}

void	update_cmd_path(t_args *args)
{
	int	i;

	args->key_values = ft_split(args->env_path, '=');
	args->paths = ft_split(args->key_values[1], ':');
	free_key_values(args);
	i = 0;
	while (args->paths[i])
		i++;
	i++;
	args->full_paths = (char **)ft_calloc((i), sizeof(char *));
	i = 0;
	while (args->paths[i])
	{
		args->full_paths[i] = ft_strjoin(args->paths[i], "/");
		i++;
	}
	free_paths(args);
}

void	get_cmd_args_list(char *argv[], t_args *args)
{
	args->cmd1_args = ft_split(argv[2], ' ');
	args->cmd2_args = ft_split(argv[3], ' ');
}

void	duplicate_absolute_path(t_args *args, char **cmd_args)
{
	args->full_paths_binary = (char **)ft_calloc(2, sizeof(char *));
	if (!args->full_paths_binary)
		return ;
	args->full_paths_binary[0] = ft_strdup(cmd_args[0]);
}

void	get_full_paths_binary(t_args *args, int nth_cmd)
{
	char	**cmd_args;
	int		i;

	cmd_args = args->cmd1_args;
	if (nth_cmd == 2)
		cmd_args = args->cmd2_args;
	i = 0;
	while (args->full_paths[i])
		i++;
	i++;
	args->full_paths_binary = (char **)ft_calloc((i), sizeof(char *));
	i = 0;
	while (args->full_paths[i])
	{
		args->full_paths_binary[i]
			= ft_strjoin(args->full_paths[i], cmd_args[0]);
		i++;
	}
	free_cmd_args(&cmd_args);
	free_cmd_args_one(args);
	free_cmd_args_two(args);
	free_full_paths(args);
}
