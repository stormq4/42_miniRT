/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   light.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: pderksen <pderksen@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/04 10:07:40 by pderksen      #+#    #+#                 */
/*   Updated: 2022/10/24 16:42:06 by pderksen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "rays.h"

t_vec4	diffuse_light(t_ray *light_ray, t_ray *ray)
{
	float	dot;

	dot = get_vector_dot(light_ray->dir, ray->normal);
	if (dot < 0)
		dot = 0;
	return (get_scalar_vector(dot));
}

//mirrored = 2 * (L * n) * n - L
t_vec4	specular_light(t_ray *light_ray, t_ray *ray, t_parser *input)
{
	t_ray	mirrored;
	t_ray	view;
	float	dot_product;
	float	spec_exponent;
	float	result;

	view.dir = normalize_vector(input->cam->cord - ray->intersect);
	mirrored.dir = (get_scalar_vector(2 * (get_vector_dot(light_ray->dir, \
		ray->normal))) * ray->normal) - light_ray->dir;
	dot_product = get_vector_dot(mirrored.dir, view.dir);
	if (dot_product < 0)
		dot_product = 0;
	spec_exponent = 8;
	result = powf(dot_product, spec_exponent);
	return (get_scalar_vector(result));
}

static t_vec4	lamp_light(t_ray *ray, t_light *lamp, t_parser *input)
{
	t_ray	light_ray;
	t_vec4	brightness;
	t_vec4	dif;
	t_vec4	spec;
	float	t;

	light_ray.dir = lamp->cord - ray->intersect;
	light_ray.origen = ray->intersect + \
		(get_scalar_vector((float)0.001) * ray->normal);
	t = get_vec_length(light_ray.dir);
	light_ray.dir = normalize_vector(light_ray.dir);
	if (check_shadow(&light_ray, t, input))
		return (get_scalar_vector((float)0));
	brightness = lamp->colors * get_scalar_vector(lamp->b_rat);
	brightness = brightness * get_scalar_vector((float)168 / (t * t));
	dif = diffuse_light(&light_ray, ray) * brightness;
	spec = specular_light(&light_ray, ray, input) * brightness;
	return (dif + spec);
}

//to the power (1/2.4) = gamma correction : STILL NEEDS TO BE DONE
static void	get_pixel_color(t_ray *ray, t_vec4 total_light)
{
	t_vec4	light;
	t_vec4	object;
	t_vec4	result;

	object = ray->intersect_color * get_scalar_vector((float)1 / 255);
	light = total_light * get_scalar_vector((float)1 / 255);
	result = object * light;
	result = result * get_scalar_vector((float)255);
	if (result[0] > 255)
		result[0] = 255;
	if (result[1] > 255)
		result[1] = 255;
	if (result[2] > 255)
		result[2] = 255;
	ray->pixel_color = result;
}

/**
 * @brief 
 * 
 * @param ray 
 * @param input 
 */
void	compute_light(t_ray *ray, t_parser *input)
{
	t_list	*lst;
	t_vec4	total_light;

	total_light = input->al->colors * get_scalar_vector(input->al->a_rat);
	lst = input->l;
	while (lst)
	{
		if (lst->ct)
			total_light += lamp_light(ray, (t_light *)lst->ct, input);
		lst = lst->next;
	}
	get_pixel_color(ray, total_light);
}
