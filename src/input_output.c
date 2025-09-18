/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_output.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: regillio <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 03:54:44 by regillio          #+#    #+#             */
/*   Updated: 2025/09/18 03:54:45 by regillio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

int	redirect_input(t_args *args)
{
	int	fd_in;

	fd_in = open(args->infile, O_RDONLY, 0644);
	if (fd_in == -1)
		return (ft_printf("error: cannot read infile.\n") & 0);
	if (dup2(fd_in, STDIN_FILENO == -1))
	{
		perror("error: input redirection failed.\n");
		close(fd_in);
		return (0);
	}
	close(fd_in);
	return (fd_in);
}

int	redirect_output(t_args *args)
{
	int	fd_out;

	fd_out = open(args->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd_out == -1)
		return (ft_printf("error: cannot read outfile.\n") & 0);
	if (dup2(fd_out, STDOUT_FILENO) == -1)
	{
		perror("error: output redirection failed.\n");
		close(fd_out);
		return (0);
	}
	close(fd_out);
	return (fd_out);
}
