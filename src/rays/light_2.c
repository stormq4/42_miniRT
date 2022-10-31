/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   light_2.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: pieterderksen <pieterderksen@student.co      +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/11 17:45:06 by pieterderks   #+#    #+#                 */
/*   Updated: 2022/10/18 14:33:28 by sde-quai      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "rays.h"

/**
 * @brief checks if the ray hits a shadow
 * 
 * @param light_ray 
 * @param lamp_d 
 * @param input 
 * @return int 
 */
int	check_shadow(t_ray *light_ray, float lamp_d, t_parser *input)
{
	light_ray->t = 0;
	get_closest_intersect(light_ray, input);
	if (light_ray->t != 0 && light_ray->t < lamp_d)
		return (TRUE);
	return (FALSE);
}

/**
 * @brief Get the scalar vector object
 * 
 * @param f 
 * @return t_vec4 
 */
t_vec4	get_scalar_vector(float f)
{
	t_vec4	s_vector;

	s_vector = (t_vec4){f, f, f, 0};
	return (s_vector);
}
