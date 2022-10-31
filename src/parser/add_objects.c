/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   add_objects.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: sde-quai <sde-quai@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/28 14:32:24 by sde-quai      #+#    #+#                 */
/*   Updated: 2022/10/25 12:05:32 by sde-quai      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

/**
 * @brief 
 * 
 * @param split 
 * @param lst 
 */
void	add_sphere(char **split, t_list **lst)
{
	t_sphere	*sp;
	t_list		*new;

	if (ft_split_len(split) != 4)
		exit_error_message("mini_rt: not a valid input for sphere\n", 1);
	sp = p_malloc(sizeof(t_sphere));
	sp->center = check_and_fill_vec4(split[1]);
	sp->d = rt_atof(split[2]);
	sp->colors = check_vec_is_color(split[3]);
	new = ft_lstnew(sp);
	ft_check_malloc(new);
	ft_lstadd_back(lst, new);
}

/**
 * @brief 
 * 
 * @param split 
 * @param lst 
 */
void	add_cylinder(char **split, t_list **lst)
{
	t_cylinder	*cyl;
	t_list		*new;

	if (ft_split_len(split) != 6)
		exit_error_message("mini_rt: not a valid input for cylinder\n", 1);
	cyl = p_malloc(sizeof(t_cylinder));
	cyl->cord = check_and_fill_vec4(split[1]);
	cyl->norm = check_vec_is_norm(split[2]);
	cyl->d = rt_atof(split[3]);
	cyl->h = rt_atof(split[4]);
	cyl->colors = check_vec_is_color(split[5]);
	cyl->angle = (float)acos((double)get_vector_dot(cyl->norm, \
	(t_vec4){0, 0, 1, 0}));
	if (cyl->angle > M_PI_2)
		cyl->angle = -(M_PI - cyl->angle);
	cyl->k = get_vector_cross(cyl->norm, (t_vec4){0, 0, 1, 0});
	cyl->zmax = cyl->h / 2;
	cyl->zmin = -cyl->zmax;
	new = ft_lstnew(cyl);
	ft_check_malloc(new);
	ft_lstadd_back(lst, new);
}

/**
 * @brief 
 * 
 * @param split 
 * @param lst 
 */
void	add_plane(char **split, t_list **lst)
{
	t_plane	*pl;
	t_list	*new;

	if (ft_split_len(split) != 4)
		exit_error_message("mini_rt: not a valid input for a plane\n", 1);
	pl = p_malloc(sizeof(t_plane));
	pl->cord = check_and_fill_vec4(split[1]);
	pl->norm = check_vec_is_norm(split[2]);
	pl->colors = check_vec_is_color(split[3]);
	new = ft_lstnew(pl);
	ft_check_malloc(new);
	ft_lstadd_back(lst, new);
}
