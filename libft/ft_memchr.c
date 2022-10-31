/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memchr.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: sde-quai <sde-quai@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/02 12:55:56 by sde-quai      #+#    #+#                 */
/*   Updated: 2021/12/02 12:55:57 by sde-quai      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	char	*tmp_s;
	size_t	i;

	tmp_s = (void *)s;
	i = 0;
	while (i < n)
	{
		if ((unsigned char)tmp_s[i] == (unsigned char)c)
			return ((unsigned char *)&tmp_s[i]);
		i++;
	}
	return (NULL);
}
