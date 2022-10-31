/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   shoot.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: pderksen <pderksen@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/28 16:33:07 by pderksen      #+#    #+#                 */
/*   Updated: 2022/10/25 11:55:10 by sde-quai      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "rays.h"

/**
 * @brief Get the intersect coord in a t_vec4
 * 
 * @param ray 
 * @return t_vec4 
 */
t_vec4	get_intersect_coord(t_ray *ray)
{
	t_vec4	intersect;
	t_vec4	distance;

	distance = (t_vec4){ray->t, ray->t, ray->t, 0};
	intersect = ray->origen + (distance * ray->dir);
	return (intersect);
}

/**
 * @brief Get the closest intersect object. loops through cylinder_intersect
 * (cylinder.c), spheres* (sphere.c) & plane* (plane.c) to retireve the 
 * closest intersect of a ray.
 * 
 * @param ray 
 * @param input 
 */
void	get_closest_intersect(t_ray *ray, t_parser *input)
{
	t_list	*lst;

	lst = input->sphere;
	while (lst)
	{
		if (lst->ct)
			sphere_intersect(ray, (t_sphere *)lst->ct);
		lst = lst->next;
	}
	lst = input->plane;
	while (lst)
	{
		if (lst->ct)
			plane_intersect(ray, (t_plane *)lst->ct);
		lst = lst->next;
	}
	lst = input->cylinder;
	while (lst)
	{
		if (lst->ct)
			cylinder_intersect(ray, (t_cylinder *)lst->ct);
		lst = lst->next;
	}
}

void	adjust_norm_ray(t_ray *ray)
{
	float	angle;

	angle = acosf(get_vector_dot(ray->dir, ray->normal) \
	/ (get_vec_length(ray->dir) * get_vec_length(ray->normal)));
	if (angle < M_PI_2)
		ray->normal = -ray->normal;
	return ;
}

/**
 * @brief the closest t for each ray is found in get_closest_intersect
 * (in shoot.c) from which the closest coordinate is computed in 
 * get_intersect_coord (in shoot.c). the light is computed as well in 
 * compute_light ()
 * 
 * @param ray 
 * @param input 
 */
void	shoot_ray(t_ray *ray, t_parser *input)
{
	ray->t = 0;
	ray->intersect_color = (t_vec4){0, 0, 0, 0};
	ray->pixel_color = (t_vec4){0, 0, 0, 0};
	get_closest_intersect(ray, input);
	if (ray->t != 0)
	{
		ray->intersect = get_intersect_coord(ray);
		adjust_norm_ray(ray);
		compute_light(ray, input);
	}
	return ;
}
