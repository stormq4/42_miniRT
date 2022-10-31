/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   free_input.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: sde-quai <sde-quai@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/13 14:37:08 by sde-quai      #+#    #+#                 */
/*   Updated: 2022/10/19 14:33:14 by sde-quai      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

/**
 * @brief free allocate memory of the parser struct
 * 
 * @param input_data 
 */
void	free_input_data(t_parser *input_data)
{
	if (!input_data)
		return ;
	if (input_data->al)
		free(input_data->al);
	if (input_data->cam)
		free(input_data->cam);
	if (input_data->l)
		ft_lstclear(&input_data->l, delete_structs);
	if (input_data->cylinder)
		ft_lstclear(&input_data->cylinder, delete_structs);
	if (input_data->plane)
		ft_lstclear(&input_data->plane, delete_structs);
	if (input_data->sphere)
		ft_lstclear(&input_data->sphere, delete_structs);
	free(input_data);
}
