/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_rgba.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: sde-quai <sde-quai@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/25 11:55:27 by sde-quai      #+#    #+#                 */
/*   Updated: 2022/10/25 11:56:07 by sde-quai      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vec4.h"

/**
 * @brief Get the rgba adn bit shift the input
 * 
 * @param r red
 * @param g green
 * @param b blue
 * @param a transparency
 * @return unsigned int 
 */
static unsigned int	get_rgba(int r, int g, int b, int a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

/**
 * @brief Get the rgb color 
 * 
 * @param color 
 * @return unsigned int 
 */
unsigned int	get_rgb_color(t_vec4 color)
{
	unsigned int		result;

	result = get_rgba((int)color[0], (int)color[1], (int)color[2], 255);
	return (result);
}
