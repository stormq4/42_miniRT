/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init_screen.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: sde-quai <sde-quai@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/03 10:06:28 by sde-quai      #+#    #+#                 */
/*   Updated: 2022/10/26 13:54:41 by sde-quai      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

/**
 * @brief Hook for the ESC key. Mutex is locked to declare that 
 * the g_img is gone.
 * 
 * @param param 
 */
static void	hook(void *param)
{
	t_screen	*screen;

	screen = param;
	if (mlx_is_key_down(screen->mlx, MLX_KEY_ESCAPE))
	{
		pthread_mutex_lock(&screen->img_mutex);
		*(screen->esc_check) = TRUE;
		mlx_close_window(screen->mlx);
		pthread_mutex_unlock(&screen->img_mutex);
	}
}

/**
 * @brief hook for closing the screen with the red cross. Mutex is locked 
 * to declare that the g_img is gone.
 * 
 * @param param 
 */
static void	close_hook(void *param)
{
	t_screen	*screen;

	screen = param;
	pthread_mutex_lock(&screen->img_mutex);
	*(screen->esc_check) = TRUE;
	mlx_close_window(screen->mlx);
	pthread_mutex_unlock(&screen->img_mutex);
}

/**
 * @brief Init screen uses the MLX library to render the pixels to the screen.
 * threads are used to determine each pixel which are initialized in 
 * init_threads (in rays/threads.c). In ray_trace_threads(rays/threads.c) the
 * threads are fired to determine each pixel. The hook function is for the ESC
 * key. merge_mutex_threads (in rays/threads.c) frees the allocated memory and
 * destroys the mutexes and joins the threads.
 * 
 * @param input_data 
 */
void	init_screen(t_parser *input_data)
{
	t_screen		screen;
	t_pixel_thread	pt[THREAD_NR];
	pthread_mutex_t	mutex;
	int				esc_check;

	esc_check = FALSE;
	screen.esc_check = &esc_check;
	screen.mlx = mlx_init(S_WIDTH, S_HEIGHT, "MINI_RT", true);
	if (!screen.mlx)
		exit(EXIT_FAILURE);
	screen.g_img = mlx_new_image(screen.mlx, S_WIDTH, S_HEIGHT);
	if (!screen.g_img)
		exit(EXIT_FAILURE);
	screen.g_img->pixels = ft_memset((screen.g_img)->pixels, 0, \
	(screen.g_img)->width * (screen.g_img)->height * sizeof(int));
	init_threads(pt, &screen, input_data, &mutex);
	ray_trace_threads(pt);
	mlx_image_to_window(screen.mlx, screen.g_img, 0, 0);
	mlx_close_hook(screen.mlx, close_hook, &screen);
	mlx_loop_hook(screen.mlx, &hook, &screen);
	mlx_loop(screen.mlx);
	mlx_terminate(screen.mlx);
	merge_mutex_threads(pt);
}
