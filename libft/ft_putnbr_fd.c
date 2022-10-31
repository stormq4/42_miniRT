/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_putnbr_fd.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: sde-quai <sde-quai@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/02 12:56:22 by sde-quai      #+#    #+#                 */
/*   Updated: 2022/01/12 11:34:03 by stormdequay   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_putnbr_rec(long long n, int fd)
{
	if (n >= 10)
	{
		ft_putnbr_rec(n / 10, fd);
		ft_putchar_fd(n % 10 + '0', fd);
	}
	if (n < 10)
		ft_putchar_fd(n + '0', fd);
}

void	ft_putnbr_fd(int n, int fd)
{
	long long	nbr;

	nbr = n;
	if (n < 0)
	{
		nbr = -nbr;
		ft_putchar_fd('-', fd);
	}
	ft_putnbr_rec(nbr, fd);
}
