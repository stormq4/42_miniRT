/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: sde-quai <sde-quai@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/27 10:31:30 by sde-quai      #+#    #+#                 */
/*   Updated: 2022/10/18 13:35:39 by sde-quai      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

/**
 * @brief exits with exit(1) with an appropriate errormessage
 * 
 * @param str 
 * @param exit_code 
 */
void	exit_error_message(char *str, int exit_code)
{
	ft_putstr_fd("Error\n", 2);
	ft_putstr_fd(str, 2);
	exit(exit_code);
}

/**
 * @brief delete the structs for the lstclear function
 * 
 * @param ct 
 */
void	delete_structs(void *ct)
{
	if (ct)
		free(ct);
}
