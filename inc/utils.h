/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: sde-quai <sde-quai@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/27 10:34:30 by sde-quai      #+#    #+#                 */
/*   Updated: 2022/10/25 12:08:01 by sde-quai      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# define S_WIDTH 1350
# define S_HEIGHT 750
# define THREAD_NR 7

# include <fcntl.h>
# include <limits.h>
# include <stdio.h>
# include <pthread.h>
# include "libft.h"
# include "MLX42.h"
# include "get_next_line.h"
# include "vec4.h"

typedef struct s_screen {
	mlx_t			*mlx;
	mlx_image_t		*g_img;
	pthread_mutex_t	img_mutex;
	int				*esc_check;
}				t_screen;

// utils.c
void			exit_error_message(char *str, int exit_code);
void			delete_structs(void *ct);

// verify_input.c
int				test_input_file(int argc, char **argv);

// get_rgba.c
unsigned int	get_rgb_color(t_vec4 color);

#endif
