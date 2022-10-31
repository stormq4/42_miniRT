/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cylinder.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: sde-quai <sde-quai@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/04 16:26:41 by sde-quai      #+#    #+#                 */
/*   Updated: 2022/10/25 12:00:59 by sde-quai      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "rays.h"

/**
 * @brief returns the hitpoint of the cylinder.
 * 
 * @param cu 
 * @param v_rot 
 * @param v_orig 
 * @param cylinder 
 * @return float 
 */
static float	return_cyl_intersect(t_compute_cyl *cu, t_vec4 v_rot, \
t_vec4 v_orig, t_cylinder *cylinder)
{
	if ((cu->z1 < cylinder->zmin && cu->z2 < cylinder->zmin) || \
	(cu->z2 > cylinder->zmax && cu->z1 > cylinder->zmax))
		return (0);
	determine_cyl_intersect(cu, v_rot, v_orig, cylinder);
	if (cu->t1 <= 0)
		return (cu->t2);
	if (cu->t2 < cu->t1 && cu->t2 > 0)
		return (cu->t2);
	else
		return (cu->t1);
}

/**
 * @brief Get the cylinder closest intersect by applying get_rodriquez_rotation
 * (cylinder_utils.c) on the direction of the ray and the origin of the 
 * cylinder. The ABC formula is used fill_abc_cylinder (cylinder_utils.c) 
 * to determine the hitpoints in an infinite long cylinder. Then the intersetc
 * in the finite long cylinder is determined return_intersect (cylinder.c).
 * 
 * @param ray 
 * @param cylinder 
 * @return float 
 */
static float	get_cylinder_closest_intersect(t_ray *ray, t_cylinder *cylinder)
{
	t_vec4			v_rot;
	t_vec4			v_orig;
	t_compute_cyl	cu;

	v_rot = get_rodriquez_rotation(ray->dir, cylinder->angle, cylinder->k);
	v_orig = get_rodriquez_rotation(ray->origen - cylinder->cord, \
	cylinder->angle, cylinder->k);
	fill_abc_cylinder(&cu, v_rot, v_orig, cylinder);
	if (cu.d < 0)
		return (0);
	if (cu.d == 0)
	{
		cu.t1 = (-cu.b) / (2 * cu.a);
		cu.z1 = v_orig[2] + cu.t1 * v_rot[2];
		if (cu.z1 < cylinder->zmin || cu.z1 > cylinder->zmax)
			return (0);
		return (cu.t1);
	}
	cu.t1 = (-cu.b + sqrt(cu.d)) / (2 * cu.a);
	cu.t2 = (-cu.b - sqrt(cu.d)) / (2 * cu.a);
	cu.z1 = v_orig[2] + cu.t1 * v_rot[2];
	cu.z2 = v_orig[2] + cu.t2 * v_rot[2];
	return (return_cyl_intersect(&cu, v_rot, v_orig, cylinder));
}

/**
 * @brief Calculates and returns the normal at the hitpoint of the cylinder.
 * Normal is first calculated in rodriquez rotated space. hence the 
 * calculated normal is rotated back to global space with negative angle
 * 
 * @param ray 
 * @param cylinder 
 * @return t_vec4 
 */
static t_vec4	cylinder_normal(t_ray *ray, t_cylinder *cylinder)
{
	t_vec4			v_dir;
	t_vec4			v_orig;
	t_vec4			hit_point;
	t_vec4			hit_norm;

	v_dir = get_rodriquez_rotation(ray->dir, cylinder->angle, cylinder->k);
	v_orig = get_rodriquez_rotation(ray->origen - cylinder->cord, \
cylinder->angle, cylinder->k);
	hit_point = v_orig + get_scalar_vector(ray->t) * v_dir;
	if (hit_point[2] == (cylinder->h / 2) || \
	hit_point[2] > (cylinder->h / 2) - 0.001)
		return (get_rodriquez_rotation(cylinder->norm, \
		-cylinder->angle, cylinder->k));
	if (hit_point[2] == -(cylinder->h / 2) || \
	hit_point[2] < -(cylinder->h / 2) + 0.001)
		return (get_rodriquez_rotation(-cylinder->norm, \
		-cylinder->angle, cylinder->k));
	hit_norm = (t_vec4){hit_point[0], hit_point[1], 0, 0};
	hit_norm = normalize_vector(hit_norm);
	hit_norm = get_rodriquez_rotation(hit_norm, -cylinder->angle, cylinder->k);
	return (hit_norm);
}

/**
 * @brief retrieves the closest intersect of a cylinder and adjust the t value.
 * If found the color is adjusted and the normal of the hitpoint on the 
 * cylinder.
 * 
 * @param ray 
 * @param cylinder 
 */
void	cylinder_intersect(t_ray *ray, t_cylinder *cylinder)
{
	float	t;

	t = get_cylinder_closest_intersect(ray, cylinder);
	if (t < 0 || t == 0)
		return ;
	if (ray->t == 0 || t < ray->t)
	{
		ray->t = t;
		ray->intersect_color = cylinder->colors;
		ray->normal = cylinder_normal(ray, cylinder);
	}
}
