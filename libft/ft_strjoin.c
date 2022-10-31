/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strjoin.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: sde-quai <sde-quai@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/02 12:56:49 by sde-quai      #+#    #+#                 */
/*   Updated: 2022/01/12 11:35:30 by stormdequay   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_strjoin_calc(char const *s1, char const *s2, \
char *str, size_t s_len[2])
{
	size_t	i;

	i = 0;
	while (i < s_len[0])
	{
		str[i] = s1[i];
		i++;
	}
	i = 0;
	while (i < s_len[1])
	{
		str[i + s_len[0]] = s2[i];
		i++;
	}
	str[i + s_len[0]] = '\0';
	return (str);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	s_len[2];
	char	*str;

	if (!s1 || !s2)
		return (NULL);
	s_len[0] = ft_strlen(s1);
	s_len[1] = ft_strlen(s2);
	str = malloc((s_len[0] + s_len[1]) * sizeof(char) + 1);
	if (!str)
		return (NULL);
	str = ft_strjoin_calc(s1, s2, str, s_len);
	return (str);
}
