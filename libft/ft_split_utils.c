/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_split_utils.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: stormdequay <stormdequay@student.codam.      +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/12 11:29:19 by stormdequay   #+#    #+#                 */
/*   Updated: 2022/09/28 16:40:54 by sde-quai      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief null terminates the last char * allocated in the 2d array with NULL
 * 
 * @param cmd1_2d 2d array
 */
void	ft_split_null_termininate(char **cmd1_2d)
{
	int	i;

	i = 0;
	while (cmd1_2d[i])
		i++;
	cmd1_2d[i] = NULL;
}

void	ft_split_free(char **split)
{
	size_t	i;

	if (!split)
		return ;
	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

int	ft_split_len(char **split)
{
	int	i;

	i = 0;
	if (!split)
		return (i);
	while (split[i])
		i++;
	return (i);
}
