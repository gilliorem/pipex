
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

typedef struct s_args
{
	char	*env_path;
	int		argc;
	char	**argv;
	char	**envp;
	char	**key_values;
	char	**paths;
	char	**full_paths;
	char	**cmd1_args;
	char	**cmd2_args;
	char	*full_path_binary;
	char	**full_paths_binary;
	int		fds[2];

	char	*infile;
	char	*outfile;
} t_args;

t_args	*init_args(char **argv, char **envp);
void	get_env_path(char **env, t_args *args);
int	update_cmd_path(t_args *args);
void	get_cmd_args_list(char **argv, t_args *args);
void	get_full_paths_binary(t_args *args, int nth_cmd);
int		check_cmd(char *full_path_binary);
void	run_cmds(t_args *args, int ntg_cmd);


void    free_key_values(t_args *args);
void    free_paths(t_args *args);
void    free_cmd_args(t_args *args);
void    free_full_paths_binary(char ***full_paths_binary);
void    free_everything(t_args *args);
void    clean_struct(t_args *args);
#endif
