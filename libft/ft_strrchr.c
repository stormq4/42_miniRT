/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strrchr.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: sde-quai <sde-quai@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/02 12:57:20 by sde-quai      #+#    #+#                 */
/*   Updated: 2021/12/02 12:57:20 by sde-quai      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t	len;

	len = ft_strlen(s) + 1;
	while (len)
	{
		if (s[len - 1] == (char)c)
			return ((char *)&s[len - 1]);
		len--;
	}
	return (NULL);
}
