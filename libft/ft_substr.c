/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_substr.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: sde-quai <sde-quai@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/02 12:57:26 by sde-quai      #+#    #+#                 */
/*   Updated: 2022/01/12 11:35:53 by stormdequay   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_second_substr(const char *s, char *sub_s, size_t len)
{
	size_t	i;

	i = 0;
	while (i < len && s[i])
	{
		sub_s[i] = s[i];
		i++;
	}
	sub_s[i] = '\0';
	return (sub_s);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sub_s;
	size_t	i;
	size_t	size;

	if (!s)
		return (NULL);
	size = ft_strlen(s);
	if (size < start)
		return (ft_strdup(""));
	i = 0;
	if (len > ft_strlen(s) - start)
		return (ft_strdup(s + start));
	sub_s = ft_calloc((len + 1), sizeof(char));
	if (!sub_s)
		return (sub_s);
	i = 0;
	while (s[i] && start > i)
		i++;
	s += i;
	return (ft_second_substr(s, sub_s, len));
}
