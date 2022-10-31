/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.h                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: sde-quai <sde-quai@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/28 12:11:11 by sde-quai      #+#    #+#                 */
/*   Updated: 2022/09/27 13:26:08 by sde-quai      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# define BUFFER_SIZE 42
# include "libft.h"
# include <unistd.h>

char	*get_next_line(int fd);
char	*gnl_read_buffer(char *line, char *buffer, int fd);
char	*gnl_reindex_buf(char *buffer, char *line);
size_t	gnl_strlen(char *str, int boolean);

#endif
