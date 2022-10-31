/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   threads.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: sde-quai <sde-quai@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/17 14:21:43 by sde-quai      #+#    #+#                 */
/*   Updated: 2022/10/19 14:11:54 by sde-quai      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "rays.h"

/**
 * @brief initializes thread structs and mutex for shared data. init_camera 
 * (in camera.c) initializes the camera for the simulation.
 * 
 */
void	init_threads(t_pixel_thread pt[THREAD_NR], \
t_screen *screen, t_parser *input, pthread_mutex_t *mutex)
{
	int			i;
	t_camera2	*cam2;

	cam2 = p_malloc(sizeof(t_camera2));
	init_camera2(cam2, input->cam);
	if (pthread_mutex_init(mutex, NULL))
		exit(1);
	if (pthread_mutex_init(&screen->img_mutex, NULL))
		exit(1);
	i = 0;
	while (i < THREAD_NR)
	{
		pt[i].mutex = mutex;
		pt[i].img_mutex = &screen->img_mutex;
		pt[i].g_img = screen->g_img;
		pt[i].input = input;
		pt[i].cam2 = cam2;
		pt[i].esc_check = screen->esc_check;
		i++;
	}
}

/**
 * @brief destroys allocated memory and joins threads
 * 
 */
void	merge_mutex_threads(t_pixel_thread pt[THREAD_NR])
{
	int	i;

	i = 0;
	pthread_mutex_destroy(pt[0].img_mutex);
	pthread_mutex_destroy(pt[0].mutex);
	free(pt[0].cam2);
	while (i < THREAD_NR)
	{
		pthread_join(pt[i].t_id, NULL);
		i++;
	}
}

/**
 * @brief THREAD_NR threads are created. And the function start_tracing 
 * (in camera.c) is called as the beginning of the simulation. If a thread
 * fails then the threads upon that thread is deleted and exit is called.
 * 
 * @param pt pixel_thread
 */
void	ray_trace_threads(t_pixel_thread pt[THREAD_NR])
{
	int	i;
	int	j;

	i = 0;
	while (i < THREAD_NR)
	{
		if (pthread_create(&pt[i].t_id, NULL, start_tracing, &pt[i]))
		{
			j = 0;
			while (j < i)
			{
				pthread_join(pt[j].t_id, NULL);
				j++;
			}	
			exit(EXIT_FAILURE);
		}
		i++;
	}
}
