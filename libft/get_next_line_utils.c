/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line_utils.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: sde-quai <sde-quai@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/28 12:15:43 by sde-quai      #+#    #+#                 */
/*   Updated: 2022/01/21 16:01:59 by sde-quai      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdlib.h>

size_t	gnl_strlen(char *str, int boolean)
{
	size_t	len;

	len = 0;
	while (str[len] != 0 && len < BUFFER_SIZE && str[len] \
	!= '\n' && boolean == TRUE)
		len++;
	while (str[len] != 0 && boolean == FALSE)
		len++;
	return (len);
}

static void	gnl_bzero(char	*str, size_t i)
{
	while (i < BUFFER_SIZE)
	{
		str[i] = 0;
		i++;
	}
}

static void	*gnl_memmove(void *dst, const void *src, size_t len)
{
	size_t	i;

	if (dst == NULL && src == NULL)
		return (NULL);
	i = 0;
	if (dst > src)
	{
		while (len > 0)
		{
			((char *)dst)[len - 1] = ((char *)src)[len - 1];
			len--;
		}
		return (dst);
	}
	while (len > i)
	{
		((char *)dst)[i] = ((char *) src)[i];
		i++;
	}
	return (dst);
}

char	*gnl_reindex_buf(char *buffer, char *line)
{
	size_t	i[2];
	char	*tmp;
	size_t	str_lenbuf;

	str_lenbuf = gnl_strlen(buffer, TRUE);
	tmp = malloc((gnl_strlen(line, FALSE) + str_lenbuf + 2) * sizeof(char));
	if (!tmp)
		exit(1);
	i[1] = 0;
	while (line[i[1]] != '\0')
	{
		tmp[i[1]] = line[i[1]];
		i[1]++;
	}
	i[0] = 0;
	while (i[0] < str_lenbuf + 1 && i[0] < BUFFER_SIZE)
	{
		tmp[i[1] + i[0]] = buffer[i[0]];
		i[0]++;
	}
	gnl_memmove(buffer, buffer + i[0], BUFFER_SIZE - i[0]);
	tmp[i[1] + i[0]] = 0;
	gnl_bzero(buffer, BUFFER_SIZE - i[0]);
	free(line);
	return (tmp);
}

char	*gnl_read_buffer(char *line, char *buffer, int fd)
{
	int		read_i;
	size_t	line_len;

	read_i = read(fd, buffer, BUFFER_SIZE);
	if (read_i < 0)
		return (NULL);
	while (read_i)
	{
		if (read_i < 0)
			return (NULL);
		line = gnl_reindex_buf(buffer, line);
		if (!line)
			return (NULL);
		line_len = gnl_strlen(line, FALSE);
		if (line_len && line[line_len - 1] == '\n')
			return (line);
		read_i = read(fd, buffer, BUFFER_SIZE);
	}
	return (line);
}
