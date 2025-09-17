#include "../include/pipex.h"

void	free_key_values(t_args *args)
{
	int	i;

	i = 0;
	if (!args->key_values)
		return ;
	while (args->key_values[i])
	{
		free(args->key_values[i]);
		args->key_values[i] = NULL;
		i++;
	}
	free(args->key_values);
	args->key_values = NULL;
}

void free_paths(t_args *args)
{
  int i;

  i = 0;
  if (!args->paths)
	  return ;
  while (args->paths[i])
  {
    free(args->paths[i]);
	args->paths[i] = NULL;
    i++;
  }
  free(args->paths);
  args->paths = NULL;
}

void	free_cmd_args(t_args *args)
{
	int	i;

	i = 0;
	if (!args->cmd_args)
		return ;
	while (args->cmd_args[i])
	{
		free(args->cmd_args[i]);
		args->cmd_args[i] = NULL;
		i++;
	}
	free(args->cmd_args);
	args->cmd_args = NULL;
}

void	free_full_paths_binary(int i, char **full_paths_binary)
{
	if (!full_paths_binary)
		return ;
	while (i >= 0)
	{
		free(full_paths_binary[i]);
		full_paths_binary[i] = NULL;
		i--;
	}
}

void	free_everything(t_args *args)
{
	if (args->key_values)
		free_key_values(args);
	if (args->full_paths)
		free_paths(args);
	if (args->cmd_args)
		free_cmd_args(args);
}

void	clean_struct(t_args *args)
{
	if (!args->full_paths_binary)
		return ;
	free(args->full_paths_binary);
	if (!args)
		return ;
	free(args);
}
