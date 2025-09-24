/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: regillio <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 09:45:21 by regillio          #+#    #+#             */
/*   Updated: 2025/06/13 10:16:00 by regillio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"

/* I use strchr to point to the newline char */

ssize_t	ft_strlen_line(const char *s)
{
	ssize_t	i;

	i = 0;
	if (!s)
		return (i);
	while (s[i])
		i++;
	return (i);
}

/* join the buf that comes out the read()
 * with our storage (static buf)
 */

char	*ft_strjoin_line(char *s1, char *s2)
{
	char	*str_join;
	ssize_t	str_join_len;
	ssize_t	i;

	str_join_len = ft_strlen(s1) + ft_strlen(s2);
	str_join = (char *)malloc((str_join_len + 1) * sizeof(char));
	if (!str_join)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		str_join[i] = s1[i];
		i++;
	}
	i = 0;
	while (s2[i])
	{
		str_join[i + ft_strlen(s1)] = s2[i];
		i++;
	}
	str_join[ft_strlen(s1) + i] = '\0';
	free(s1);
	return (str_join);
}

/* make a copy of my storage (static_buf) and be
 * able to free the original one */
/* I use substr to form my new line. Once I found my starting
 * point using strchr I make my line out of the storage (static_buf)
 * since we will return this, we will free in our main()
 */
