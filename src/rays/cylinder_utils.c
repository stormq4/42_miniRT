/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cylinder_utils.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: sde-quai <sde-quai@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/06 16:25:02 by sde-quai      #+#    #+#                 */
/*   Updated: 2022/10/19 11:04:56 by sde-quai      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "rays.h"

/**
 * @brief Get the rodriquez rotation of the cylinder. The cylinder needs to be
 * rotated such that it stands straight in order to compute the hitpoints. Also
 * the ray needs to be rotated acording to the formula.
 * 
 * @param vec 
 * @param angle 
 * @param k 
 * @return t_vec4 
 */
t_vec4	get_rodriquez_rotation(t_vec4 vec, float angle, t_vec4 k)
{
	t_vec4	rod;

	rod = vec * (float)cos(angle) + \
	get_vector_cross(k, vec) * (float)sin(angle) + \
	k * get_vector_dot(k, vec) * (1 - (float)cos(angle));
	return (rod);
}

/**
 * @brief the abc formula is applied in order to determine where the ray hits
 * the infinitely tall cylinder.
 * 
 * @param cu 
 * @param v_rot 
 * @param v_orig 
 * @param cyl 
 */
void	fill_abc_cylinder(t_compute_cyl *cu, t_vec4 v_rot, t_vec4 v_orig, \
t_cylinder *cyl)
{
	cu->a = v_rot[0] * v_rot[0] + v_rot[1] * v_rot[1];
	cu->b = 2 * v_rot[0] * v_orig[0] + 2 * v_rot[1] * v_orig[1];
	cu->c = v_orig[0] * v_orig[0] + v_orig[1] * v_orig[1] - pow(cyl->d / 2, 2);
	cu->d = cu->b * cu->b - 4 * cu->a * cu->c;
}

/**
 * @brief The intersect of the ylinder is determined wether it hits on top, 
 * bottem or side of the cylinder.
 * 
 * @param cu 
 * @param v_rot 
 * @param v_orig 
 * @param cylinder 
 */
void	determine_cyl_intersect(t_compute_cyl *cu, t_vec4 v_rot, t_vec4 v_orig, \
t_cylinder *cylinder)
{
	if (cu->z1 > cylinder->zmin && cu->z1 < cylinder->zmax)
	{
		if (cu->z2 < cylinder->zmin)
			cu->t2 = (cylinder->zmin - v_orig[2]) / v_rot[2];
		else if (cu->z2 > cylinder->zmax)
			cu->t2 = (cylinder->zmax - v_orig[2]) / v_rot[2];
	}
	if (cu->z2 > cylinder->zmin && cu->z2 < cylinder->zmax)
	{
		if (cu->z1 < cylinder->zmin)
			cu->t1 = (cylinder->zmin - v_orig[2]) / v_rot[2];
		else if (cu->z1 > cylinder->zmax)
			cu->t1 = (cylinder->zmax - v_orig[2]) / v_rot[2];
	}
	if (cu->z1 < cylinder->zmin && cu->z2 > cylinder->zmax)
	{
		cu->t1 = (cylinder->zmin - v_orig[2]) / v_rot[2];
		cu->t2 = (cylinder->zmax - v_orig[2]) / v_rot[2];
	}
	if (cu->z2 < cylinder->zmin && cu->z1 > cylinder->zmax)
	{
		cu->t1 = (cylinder->zmax - v_orig[2]) / v_rot[2];
		cu->t2 = (cylinder->zmin - v_orig[2]) / v_rot[2];
	}
}
