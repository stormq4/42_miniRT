/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_itoa.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: sde-quai <sde-quai@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/02 12:54:50 by sde-quai      #+#    #+#                 */
/*   Updated: 2022/01/12 11:33:40 by stormdequay   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_itoa_fill(char	*str, int n, int pow, int i)
{
	while (pow)
	{
		str[i] = n / (int)ft_power(10, pow - 1) + '0';
		n %= (int)ft_power(10, pow - 1);
		pow--;
		i++;
	}
	str[i] = '\0';
	return (str);
}

static char	*ft_itoa_calc(int n, int pow)
{
	char	*str;
	int		i;

	i = 0;
	if (n < 0)
	{
		str = malloc((pow + 2) * sizeof(char));
		if (!str)
			return (NULL);
		str[i] = '-';
		i++;
		n = -n;
	}
	else
	{
		str = malloc((pow + 1) * sizeof(char));
		if (!str)
			return (NULL);
	}
	str = ft_itoa_fill(str, n, pow, i);
	return (str);
}

char	*ft_itoa(int n)
{
	int		pow;
	int		n_1;
	char	*str;

	if (!n)
		return (ft_strdup("0"));
	else if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	pow = 0;
	n_1 = n;
	while (n_1)
	{
		n_1 /= 10;
		pow++;
	}
	str = ft_itoa_calc(n, pow);
	if (!str)
		return (NULL);
	return (str);
}
