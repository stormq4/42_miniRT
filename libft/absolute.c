/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   absolute.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: sde-quai <sde-quai@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/27 15:51:24 by sde-quai      #+#    #+#                 */
/*   Updated: 2022/02/02 09:26:17 by sde-quai      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

float	absolute_float(float abs)
{
	if (abs < 0)
		abs = -abs;
	return (abs);
}

int	absolute_int(int abs)
{
	if (abs < 0)
		abs = -abs;
	return (abs);
}

long	absolute_long(long abs)
{
	if (abs < 0)
		abs = -abs;
	return (abs);
}
