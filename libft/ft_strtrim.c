/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strtrim.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: sde-quai <sde-quai@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/02 12:57:23 by sde-quai      #+#    #+#                 */
/*   Updated: 2021/12/02 12:57:23 by sde-quai      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*str;
	size_t	str_len;
	size_t	i;

	if (!s1)
		return (0);
	while (ft_strchr(set, *s1) && *s1)
		s1++;
	str_len = ft_strlen(s1);
	i = 0;
	while (ft_strchr(set, s1[str_len - i - 1]) && *s1)
		i++;
	str = ft_substr(s1, 0, str_len - i);
	if (!str)
		return (ft_strdup(""));
	return (str);
}
