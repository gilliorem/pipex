#include "../include/pipex.h"

static void free_string_array(char ***array)
{
    int index;

    if (!array || !*array)
        return ;
    index = 0;
    while ((*array)[index])
    {
        free((*array)[index]);
        (*array)[index] = NULL;
        index++;
    }
    free(*array);
    *array = NULL;
}

void    free_key_values(t_args *args)
{
    free_string_array(&args->key_values);
}

void    free_paths(t_args *args)
{
    free_string_array(&args->paths);
}

void    free_cmd_args(t_args *args)
{
    free_string_array(&args->cmd1_args);
    free_string_array(&args->cmd2_args);
}

void    free_full_paths_binary(char ***full_paths_binary)
{
    free_string_array(full_paths_binary);
}

void    free_everything(t_args *args)
{
    if (!args)
        return ;
    free_key_values(args);
    free_paths(args);
    free_string_array(&args->full_paths);
    free_cmd_args(args);
    free_full_paths_binary(&args->full_paths_binary);
}

void    clean_struct(t_args *args)
{
    if (!args)
        return ;
    free_everything(args);
    free(args);
}
