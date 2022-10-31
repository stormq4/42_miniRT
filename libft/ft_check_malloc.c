/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_check_malloc.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: sde-quai <sde-quai@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/17 10:04:50 by sde-quai      #+#    #+#                 */
/*   Updated: 2022/09/29 14:05:48 by sde-quai      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

void	*p_malloc(size_t size)
{
	void	*ptr;

	ptr = malloc(size);
	ft_check_malloc(ptr);
	return (ptr);
}

void	ft_check_malloc(void *ptr)
{
	if (!ptr)
		exit(1);
}
