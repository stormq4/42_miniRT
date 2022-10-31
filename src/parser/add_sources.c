/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   add_sources.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: sde-quai <sde-quai@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/28 14:29:11 by sde-quai      #+#    #+#                 */
/*   Updated: 2022/10/25 12:07:35 by sde-quai      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

/**
 * @brief check_and_fill_vec4 (in utils_vec.c)
 * 
 * @param split 
 * @param al 
 */
void	fill_ambient_light(char **split, t_alight **al)
{
	if (ft_split_len(split) != 3)
		exit_error_message("mini_rt: not a valid input for \
ambient lighting1\n", 1);
	if (*al)
		exit_error_message("mini_rt: double ambient lighting input\n", 1);
	*al = p_malloc(sizeof(t_alight));
	(*al)->a_rat = rt_atof(split[1]);
	if ((*al)->a_rat < 0 || (*al)->a_rat > 1.0)
		exit_error_message("mini_rt: not a valid input for \
ambient lighting2\n", 1);
	(*al)->colors = check_vec_is_color(split[2]);
}

/**
 * @brief run make bonus for multiple light spots.
 * 
 * @param split 
 * @param lst 
 */
void	fill_light(char **split, t_list **lst)
{
	t_light	*l;
	t_list	*new;

	if (ft_split_len(split) != 4)
		exit_error_message("mini_rt: not a valid input for lighting\n", 1);
	if (*lst && !RT_BONUS)
		exit_error_message("mini_rt: double multiple input\n", 1);
	l = p_malloc(sizeof(t_light));
	l->cord = check_and_fill_vec4(split[1]);
	l->b_rat = rt_atof(split[2]);
	if (l->b_rat < 0 || l->b_rat > 1.0)
		exit_error_message("mini_rt: not a valid input for lighting\n", 1);
	l->colors = check_vec_is_color(split[3]);
	new = ft_lstnew(l);
	ft_check_malloc(new);
	ft_lstadd_back(lst, new);
}

/**
 * @brief 
 * 
 * @param split 
 * @param cam 
 */
void	fill_camera(char **split, t_camera **cam)
{
	if (ft_split_len(split) != 4)
		exit_error_message("mini_rt: not a valid input for camera\n", 1);
	if (*cam)
		exit_error_message("mini_rt: not a valid input for camera\n", 1);
	*cam = p_malloc(sizeof(t_camera));
	(*cam)->cord = check_and_fill_vec4(split[1]);
	(*cam)->norm = check_vec_is_norm(split[2]);
	(*cam)->fov = rt_atof(split[3]);
	if ((*cam)->fov < 0 || (*cam)->fov > 180)
		exit_error_message("mini_rt: not a valid input for camera\n", 1);
}
