/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: regillio <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 04:05:46 by regillio          #+#    #+#             */
/*   Updated: 2025/09/18 04:07:19 by regillio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include <fcntl.h> // open
# include <string.h> // strerror
# include <unistd.h> // access					 
# include <stdio.h> // perror
# include "../libft/libft.h"
# include <errno.h>
# include <sys/wait.h>
# include <unistd.h>
# include <stdlib.h>

typedef struct s_args
{
	char		*env_path;
	int			argc;
	char		**argv;
	char		**envp;
	char		**key_values;
	char		**paths;
	char		**full_paths;
	char		**cmd1_args;
	char		**cmd2_args;
	char		*full_path_binary;
	char		**full_paths_binary;
	int			fds[2];
	char		*infile;
	char		*outfile;
	int			status;
	int			exit_status;
	pid_t		child_one;
	pid_t		child_two;
}				t_args;

t_args	*init_args(char **argv, char **envp);

/* Path to binary */
void	get_env_path(char **env, t_args *args);
void	update_cmd_path(t_args *args);
void	get_cmd_args_list(char **argv, t_args *args);
void	duplicate_absolute_path(t_args *args, char **cmd_args);
void	get_full_paths_binary(t_args *args, int nth_cmd);

/* Command */
void	run_cmds(t_args *args, int ntg_cmd);

/* Exit */
void	print_error_message(char *cmd_name, char *msg);
void	exit_on_cmd_path(t_args *args, char *cmd_name);
void	exit_on_binary(t_args *args, char *cmd_name);
void	exit_on_cmd_list(t_args *args, char *cmd_name);
void	close_fds(t_args *args);

/* input output redirection */
int		redirect_input(t_args *args);
int		redirect_output(t_args *args);

/* child_process */
int		on_wrong_child_pid(t_args *args);
void	execute_first_child(t_args *args);
void	execute_second_child(t_args *args);
void	wait_children(t_args *args);

/* free */
void	free_key_values(t_args *args);
void	free_paths(t_args *args);
void	free_cmd_args(char ***cmd_args);
void	free_full_paths(t_args *args);
void	free_full_paths_binary(char ***full_paths_binary);
void	free_cmd_args_one(t_args *args);
void	free_cmd_args_two(t_args *args);

/* clean up */
void	free_string_array(char ***array);
void	free_everything(t_args *args);
void	clean_struct(t_args *args);
void	clean_up(t_args *args);
#endif
