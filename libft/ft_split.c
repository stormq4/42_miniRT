/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_split.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: sde-quai <sde-quai@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/02 12:56:33 by sde-quai      #+#    #+#                 */
/*   Updated: 2022/01/19 10:51:26 by sde-quai      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_strlen_c(char *s, int c)
{
	size_t	i;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	return (i);
}

static char	**ft_cleanup(char **str_2d, size_t str_num)
{
	size_t	i;

	i = 0;
	while (i < str_num)
	{
		free((void *)str_2d[i]);
		i++;
	}
	free (str_2d);
	str_2d = NULL;
	return (str_2d);
}

static char	**ft_second_split(char **str_2d, const char *str, \
size_t str_num, char c)
{
	size_t	i;
	size_t	j;
	size_t	str_part;

	i = 0;
	while (i < str_num)
	{
		str_part = ft_strlen_c((char *)str, c);
		str_2d[i] = ft_substr(str, 0, str_part);
		if (!str_2d[i])
			return (ft_cleanup(str_2d, i - 1));
		j = 0;
		while ((j < str_part || *str == c) && *str)
		{
			j++;
			str++;
		}
		i++;
	}
	str_2d[i] = 0;
	return (str_2d);
}

static size_t	ft_count_words(const char *str, char c)
{
	size_t	str_num;
	size_t	i;

	while (*str == c)
		str++;
	str_num = 0;
	i = 0;
	while (str[i] != 0)
	{
		if ((str[i] != c && str[i + 1] == c) || \
		(str[i] != c && str[i + 1] == 0))
			str_num++;
		i++;
	}
	return (str_num);
}

char	**ft_split(const char *s, char c)
{
	char	**str_2d;
	size_t	str_num;

	if (!s)
		return (NULL);
	str_num = ft_count_words(s, c);
	str_2d = ft_calloc((str_num + 1), sizeof(char *));
	if (s[0] == 0)
	{
		str_2d[0] = 0;
		return (str_2d);
	}
	if (!str_2d)
		return (NULL);
	if (!str_num)
		return (str_2d);
	while (*s == c)
		s++;
	str_2d = ft_second_split(str_2d, s, str_num, c);
	if (!str_2d)
		return (NULL);
	return (str_2d);
}
