/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   verify_input.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: sde-quai <sde-quai@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/27 13:21:11 by sde-quai      #+#    #+#                 */
/*   Updated: 2022/10/19 10:36:37 by sde-quai      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

/**
 * @brief .rt file check
 * 
 * @param file_name 
 * @return int 
 */
static int	test_rt_file(char *file_name)
{
	if (ft_strlen(file_name) < 4)
	{
		ft_putstr_fd("Error\nmini_rt: no valid name for .rt file\n", 2);
		return (FALSE);
	}
	if (ft_strncmp(&file_name[ft_strlen(file_name) - 3], ".rt", 3))
	{
		ft_putstr_fd("Error\nmini_rt: no valid name for .rt file\n", 2);
		return (FALSE);
	}
	return (TRUE);
}

/**
 * @brief verifies if the argument of the program is an .rt file
 * 
 * @param argc 
 * @param argv 
 * @return int 
 */
int	test_input_file(int argc, char **argv)
{
	if (argc == 1)
	{
		ft_putstr_fd("Error\nmini_rt: too few arguments given\n", 2);
		return (FALSE);
	}
	else if (argc > 2)
	{
		ft_putstr_fd("Error\nmini_rt: too many arguments\n", 2);
		return (FALSE);
	}
	else if (!test_rt_file(argv[1]))
		return (FALSE);
	return (TRUE);
}
