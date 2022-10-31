/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memcmp.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: sde-quai <sde-quai@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/02 12:56:03 by sde-quai      #+#    #+#                 */
/*   Updated: 2021/12/02 12:56:03 by sde-quai      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	char	*tmp_s1;
	char	*tmp_s2;
	size_t	i;

	i = 0;
	tmp_s1 = (char *)s1;
	tmp_s2 = (char *)s2;
	while (i < n)
	{
		if (tmp_s1[i] != tmp_s2[i])
			return ((unsigned char)tmp_s1[i] - (unsigned char)tmp_s2[i]);
		i++;
	}
	return (0);
}
