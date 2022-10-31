/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   camera.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: pderksen <pderksen@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/27 17:23:08 by pderksen      #+#    #+#                 */
/*   Updated: 2022/10/26 16:09:55 by pderksen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "rays.h"

/**
 * @brief computing new camera data
 * 
 * @param cam2 t_camera2 struct to be filled
 * @param camera t_camera struct
 */
void	init_camera2(t_camera2 *cam2, t_camera *camera)
{
	t_vec4	upguide;

	upguide = (t_vec4){0, 1, 0, 0};
	cam2->cam_cord = camera->cord;
	cam2->w = tan(((camera->fov) / 2) * ((2 * M_PI) / 360));
	cam2->h = cam2->w * ((float)S_HEIGHT / S_WIDTH);
	cam2->forward = camera->norm;
	if (cam2->forward[1] == 1.00)
		cam2->right = (t_vec4){1, 0, 0, 0};
	else if (cam2->forward[1] == -1.00)
		cam2->right = (t_vec4){-1, 0, 0, 0};
	else
		cam2->right = get_vector_cross(cam2->forward, upguide);
	cam2->up = get_vector_cross(cam2->right, cam2->forward);
}

/**
 * @brief Get the ray dir and origen
 * 
 * @param cam2 t_camera2 struct
 * @param px pixelx axis
 * @param py pixel y axis
 * @return t_ray 
 */
static t_ray	get_ray_dir_and_origen(t_camera2 *cam2, int px, int py)
{
	t_vec4	dir_not_normalized;
	t_ray	ray;
	float	x;
	float	y;

	x = ((float)(2 * px) / (S_WIDTH - 1)) - 1;
	y = -1 * (((float)(2 * py) / (S_HEIGHT - 1)) - 1);
	ray.origen = cam2->cam_cord;
	dir_not_normalized = cam2->forward + (cam2->h * y * cam2->up) \
	+ (cam2->w * x * cam2->right);
	ray.dir = normalize_vector(dir_not_normalized);
	return (ray);
}

/**
 * @brief ray is calculated given the x and y of the pixel and the cam2 param
 * in get_ray_dir_and_origin (in camera.c). Then the ray is shot in 
 * shoot_ray (in shoot.c) where the closest intersect is calculated and the 
 * norm. In get_rgb_color (shoot.c) the color of the pixel is determined and 
 * put to the screen
 * 
 * @param px pixelx axis
 * @param py pixel y axis
 * @param pt pixel thread
 */
static int	ray_to_screen(int px, int py, t_pixel_thread *pt)
{
	t_ray				ray;
	unsigned int		color;

	ray = get_ray_dir_and_origen(pt->cam2, px, py);
	shoot_ray(&ray, pt->input);
	color = get_rgb_color(ray.pixel_color);
	pthread_mutex_lock(pt->img_mutex);
	if (*(pt->esc_check) == FALSE)
	{
		mlx_put_pixel(pt->g_img, px, py, color);
		pthread_mutex_unlock(pt->img_mutex);
		return (TRUE);
	}
	pthread_mutex_unlock(pt->img_mutex);
	return (FALSE);
}

/**
 * @brief each thread runs this function concurrently. i is incremented 
 * and recorded in each thread. i recorded and incremented as a static
 * variable in each thread. ray_to_screen (camera.c) calculates each pixel
 * on the screen.
 * 
 * @param arg is a t_pixel_thread *;
 * @return void*  NULL for succes
 */
void	*start_tracing(void *arg)
{
	static unsigned int	i;
	unsigned int		px;
	unsigned int		py;
	t_pixel_thread		*pt;
	unsigned int		pixel_nr;

	pixel_nr = S_WIDTH * S_HEIGHT;
	pt = (t_pixel_thread *)arg;
	pthread_mutex_lock(pt->mutex);
	while (i < pixel_nr)
	{
		px = i % S_WIDTH;
		py = i / S_WIDTH;
		i++;
		pthread_mutex_unlock(pt->mutex);
		if (!ray_to_screen(px, py, pt))
			return (NULL);
		pthread_mutex_lock(pt->mutex);
	}
	pthread_mutex_unlock(pt->mutex);
	return (NULL);
}
