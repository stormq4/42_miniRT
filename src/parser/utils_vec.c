/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils_vec.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: sde-quai <sde-quai@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/06 16:46:44 by sde-quai      #+#    #+#                 */
/*   Updated: 2022/10/25 12:09:38 by sde-quai      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

/**
 * @brief check for double commas in the string
 * 
 * @param str 
 */
static void	inspect_string_to_vec4(char *str)
{
	int		i;

	if (!str)
		exit_error_message("mini_rt: not a valid input\n", 1);
	if (str[0] == ',')
		exit_error_message("mini_rt: wrong comma\n", 1);
	i = 0;
	while (str[i])
	{
		if (i > 0)
			if (str[i] == ',' && str[i - 1] == ',')
				exit_error_message("mini_rt: double comma\n", 1);
		i++;
	}
	if (i > 0 && str[i - 1] == ',')
		exit_error_message("mini_rt: wrong comma\n", 1);
}

/**
 * @brief fills the vec4 and checks its content
 * 
 * @param str 
 * @return t_vec4 
 */
t_vec4	check_and_fill_vec4(char *str)
{
	char	**split;
	t_vec4	norm;

	inspect_string_to_vec4(str);
	split = ft_split(str, ',');
	ft_check_malloc(str);
	if (ft_split_len(split) != 3)
		exit_error_message("mini_rt: not a valid float array as input\n", 1);
	norm[0] = rt_atof(split[0]);
	norm[1] = rt_atof(split[1]);
	norm[2] = rt_atof(split[2]);
	norm[3] = 0;
	ft_split_free(split);
	return (norm);
}

/**
 * @brief check if the vector is normalized with a threshold of 1%.
 * 
 * @param str 
 * @return t_vec4 
 */
t_vec4	check_vec_is_norm(char *str)
{
	t_vec4	norm;
	float	len;

	norm = check_and_fill_vec4(str);
	len = get_vec_length(norm);
	if (len > 1.01 || len < 0.99)
		exit_error_message("mini_rt: input vector is not norm\n", 1);
	norm = normalize_vector(norm);
	return (norm);
}

t_vec4	check_vec_is_color(char *str)
{
	t_vec4	rgb;

	rgb = check_and_fill_vec4(str);
	if ((rgb[0] < 0 || rgb[0] > 255) || (rgb[1] < 0 || rgb[1] > 255) || \
	(rgb[2] < 0 || rgb[2] > 255))
		exit_error_message("mini_rt: not a valid input for color\n", 1);
	return (rgb);
}
