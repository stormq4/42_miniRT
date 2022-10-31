/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: sde-quai <sde-quai@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/28 12:10:22 by sde-quai      #+#    #+#                 */
/*   Updated: 2022/01/24 09:45:31 by sde-quai      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdlib.h>
#include <limits.h>

static char	*gnl_function(char *line, char *buffer, int fd)
{
	if (buffer[0] != 0)
	{
		line = gnl_reindex_buf(buffer, line);
		if (!line)
			return (NULL);
		if (line[gnl_strlen(line, FALSE) - 1] == '\n')
			return (line);
	}
	line = gnl_read_buffer(line, buffer, fd);
	if (!line)
		return (NULL);
	return (line);
}

char	*get_next_line(int fd)
{
	static char	buffer[BUFFER_SIZE + 1];
	char		*line;

	if (fd < 0 || fd > OPEN_MAX || read(fd, buffer, 0) == -1)
		return (NULL);
	line = malloc(sizeof(char) * 1);
	if (!line)
		return (NULL);
	line[0] = 0;
	buffer[BUFFER_SIZE] = 0;
	line = gnl_function(line, buffer, fd);
	if (!line)
		exit(1);
	if (!line[0])
	{
		free(line);
		return (NULL);
	}
	return (line);
}
