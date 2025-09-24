/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_init.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: regillio <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 12:15:06 by regillio          #+#    #+#             */
/*   Updated: 2025/08/01 12:15:07 by regillio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"

char	*init_buf(char **buf)
{
	*buf = malloc(BUFFER_SIZE + 1);
	if (!*buf)
		return (NULL);
	else
		*buf[0] = '\0';
	return (*buf);
}
