/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sphere.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: pderksen <pderksen@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/29 13:02:36 by pderksen      #+#    #+#                 */
/*   Updated: 2022/10/25 11:58:52 by sde-quai      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "rays.h"

static float	get_discriminant(t_ray *ray, t_sphere *sphere, float b)
{
	t_vec4	new_orig;
	float	a;
	float	c;
	float	d;
	float	r;

	new_orig = ray->origen - sphere->center;
	r = sphere->d / 2;
	a = 1;
	c = get_vec_length_squared(new_orig) - (r * r);
	d = (b * b) - 4 * a * c;
	return (d);
}

static float	get_sphere_closest_intersect(t_ray *ray, t_sphere *sphere)
{
	t_vec4	new_orig;
	float	d;
	float	b;
	float	t;

	new_orig = ray->origen - sphere->center;
	b = 2 * (get_vector_dot(new_orig, ray->dir));
	d = get_discriminant(ray, sphere, b);
	if (d < 0)
		return (0);
	if (d == 0)
		t = -b / 2;
	else
	{
		t = (-b - sqrt(d)) / 2;
		if (t < 0)
			t = (-b + sqrt(d)) / 2;
	}
	if (t < 0)
		return (0);
	return (t);
}

static void	get_sphere_normal(t_ray *ray, t_sphere *sphere)
{
	t_vec4	point;
	t_vec4	dir;
	t_vec4	normal;

	point = get_intersect_coord(ray);
	dir = point - sphere->center;
	normal = normalize_vector(dir);
	ray->normal = normal;
}

//
/**
 * @brief Calls the get_closest_intersect function to determine if a 
 * intersection is found if so, and the intersection is positive 
 * (in front of camera) the color and normal is e
 * 
 * @param ray 
 * @param sphere 
 */
void	sphere_intersect(t_ray *ray, t_sphere *sphere)
{
	float	t;

	t = get_sphere_closest_intersect(ray, sphere);
	if (t < 0 || t == 0)
		return ;
	if (ray->t == 0 || t < ray->t)
	{
		ray->t = t;
		ray->intersect_color = sphere->colors;
		get_sphere_normal(ray, sphere);
	}
	return ;
}
