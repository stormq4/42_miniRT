/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   vec4.h                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: sde-quai <sde-quai@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/22 16:01:40 by sde-quai      #+#    #+#                 */
/*   Updated: 2022/10/25 12:08:05 by sde-quai      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef VEC4_H
# define VEC4_H

# include <math.h>

typedef float	t_vec4 __attribute__ ((vector_size (16)));

// vector_get.c
float	get_vec_length(t_vec4 vec);
float	get_vec_length_squared(t_vec4 vec);
float	get_vector_dot(t_vec4 u, t_vec4 v);
t_vec4	get_vector_cross(t_vec4 u, t_vec4 v);
t_vec4	normalize_vector(t_vec4 vec);

#endif
