/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   rays.h                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: sde-quai <sde-quai@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/03 10:50:05 by sde-quai      #+#    #+#                 */
/*   Updated: 2022/10/25 11:53:35 by sde-quai      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYS_H
# define RAYS_H

# include "parser.h"

typedef struct s_ray
{
	t_vec4	origen;
	t_vec4	dir;
	float	t;
	t_vec4	intersect;
	t_vec4	intersect_color;
	t_vec4	pixel_color;
	t_vec4	normal;
}	t_ray;

typedef struct s_camera2
{
	float	h;
	float	w;
	t_vec4	cam_cord;
	t_vec4	forward;
	t_vec4	up;
	t_vec4	right;
}	t_camera2;

typedef struct s_compute_cyl {
	float	a;
	float	b;
	float	c;
	float	d;
	float	t1;
	float	t2;
	float	z1;
	float	z2;
}				t_compute_cyl;

typedef struct s_pixel_thread {
	pthread_t		t_id;
	pthread_mutex_t	*mutex;
	pthread_mutex_t	*img_mutex;
	mlx_image_t		*g_img;
	t_parser		*input;
	t_camera2		*cam2;
	int				*esc_check;
}				t_pixel_thread;

// camera.c
void			init_camera2(t_camera2 *cam2, t_camera *camera);
void			*start_tracing(void *arg);

// threads.c
void			ray_trace_threads(t_pixel_thread pt[THREAD_NR]);
void			merge_mutex_threads(t_pixel_thread pt[THREAD_NR]);
void			init_threads(t_pixel_thread pt[THREAD_NR], t_screen *screen, \
t_parser *input, pthread_mutex_t *mutex);

// light_2.c
int				check_shadow(t_ray *light_ray, float lamp_d, t_parser *input);
t_vec4			get_scalar_vector(float f);

// light.c
t_vec4			diffuse_light(t_ray *light_ray, t_ray *ray);
t_vec4			specular_light(t_ray *light_ray, t_ray *ray, t_parser *input);
void			compute_light(t_ray *ray, t_parser *input);

// plane.c
void			plane_intersect(t_ray *ray, t_plane *plane);

// shoot.c
unsigned int	get_rgb_color(t_vec4 color);
t_vec4			get_intersect_coord(t_ray *ray);
void			get_closest_intersect(t_ray *ray, t_parser *input);
void			shoot_ray(t_ray *ray, t_parser *input);

// sphere.c
void			sphere_intersect(t_ray *ray, t_sphere *sphere);

// cylinder.c
void			cylinder_intersect(t_ray *ray, t_cylinder *cylinder);

// cylinder_utils.h
void			determine_cyl_intersect(t_compute_cyl *cu, t_vec4 v_rot, \
				t_vec4 v_orig, t_cylinder *cylinder);
void			fill_abc_cylinder(t_compute_cyl *cu, t_vec4 v_rot, \
				t_vec4 v_orig, t_cylinder *cyl);
t_vec4			get_rodriquez_rotation(t_vec4 vec, float angle, t_vec4 k);

#endif