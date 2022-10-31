/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   p_utils.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: sde-quai <sde-quai@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/28 11:51:48 by sde-quai      #+#    #+#                 */
/*   Updated: 2022/10/18 10:51:33 by sde-quai      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

/**
 * @brief initialize the parser
 * 
 * @return t_parser* 
 */
t_parser	*init_parser(void)
{
	t_parser	*input_data;

	input_data = p_malloc(sizeof(t_parser));
	input_data->al = NULL;
	input_data->cam = NULL;
	input_data->l = NULL;
	input_data->cylinder = NULL;
	input_data->plane = NULL;
	input_data->sphere = NULL;
	return (input_data);
}

/**
 * @brief tests for double dots in the string
 * 
 * @param str 
 */
static void	check_string_is_float(char *str)
{
	int	dot_count;
	int	i;

	i = 0;
	dot_count = 0;
	while (str[i])
	{
		if (str[i] == '.')
			dot_count++;
		if (dot_count > 1)
			exit_error_message("mini_rt: not a valid float as input\n", 1);
		if (!ft_isdigit(str[i]) && str[i] != '.')
			exit_error_message("mini_rt: not a valid float as input\n", 1);
		i++;
	}
}

/**
 * @brief 
 * 
 * @param str 
 * @param sign 
 * @return float 
 */
static float	rt_atof_util(char *str, int sign)
{
	double	val;
	double	power;
	int		i;

	i = 0;
	val = 0;
	while (ft_isdigit(str[i]) && str[i])
	{
		val = 10 * val + str[i] - '0';
		i++;
	}
	if (str[i] == '.')
		i++;
	power = 1;
	while (ft_isdigit(str[i]) && str[i])
	{
		val = 10 * val + str[i] - '0';
		power *= 10;
		i++;
	}
	return ((float)(sign * val / power));
}

/**
 * @brief ascii to float for miniRT
 * 
 * @param str string to be converted
 * @return float 
 */
float	rt_atof(char *str)
{
	int		sign;

	sign = 1;
	if (*str == '-')
	{
		sign = -1;
		str++;
	}
	check_string_is_float(str);
	return (rt_atof_util(str, sign));
}
