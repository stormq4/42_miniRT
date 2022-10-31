/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: sde-quai <sde-quai@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/27 11:08:34 by sde-quai      #+#    #+#                 */
/*   Updated: 2022/10/19 10:49:44 by sde-quai      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

/**
 * @brief identifies the tokens and adds them accordingly to the parser struct.
 * fill_light, *camera & *ambient_light are found in add_sources.c. add_sphere, 
 * *cylinder & *plane are found in add_objects.c
 * 
 * @param split 2d array of the parsed line
 * @param input_data parser struct
 */
static void	add_token_to_parser(char **split, t_parser *input_data)
{
	if (!ft_strncmp("A", split[0], 2))
		fill_ambient_light(split, &input_data->al);
	else if (!ft_strncmp("L", split[0], 2))
		fill_light(split, &input_data->l);
	else if (!ft_strncmp("C", split[0], 2))
		fill_camera(split, &input_data->cam);
	else if (ft_strlen(split[0]) == 1)
		exit_error_message("mini_rt: not a valid object or source\n", 1);
	else if (!ft_strncmp("sp", split[0], 3))
		add_sphere(split, &input_data->sphere);
	else if (!ft_strncmp("cy", split[0], 3))
		add_cylinder(split, &input_data->cylinder);
	else if (!ft_strncmp("pl", split[0], 3))
		add_plane(split, &input_data->plane);
	else
		exit_error_message("mini_rt: not a valid object or source\n", 1);
}

/**
 * @brief Loops through the token list and adds it to parser struct. 
 * Errors are given with an appropriate message followed with an exit(1).
 * 
 * @param tokens 
 * @return t_parser*  
 */
static t_parser	*parse_tokens(t_list *tokens)
{
	char		**split;
	t_parser	*input_data;

	input_data = init_parser();
	while (tokens)
	{
		split = (char **)tokens->ct;
		if (!split)
			exit_error_message("mini_rt: not a valid object or source\n", 1);
		if (!split[0])
			exit_error_message("mini_rt: not a valid object or source\n", 1);
		add_token_to_parser(split, input_data);
		tokens = tokens->next;
	}
	if (!input_data->al || !input_data->cam || !input_data->l)
		exit_error_message("mini_rt: missing source in input\n", 1);
	return (input_data);
}

/**
 * @brief The parser first tokenizes the .rt file with tokenize_infile 
 * (in tokens.c) then with the tokens the parser struct is filled in 
 * parse_tokens. Several checks are done to validate input. 
 * 
 * @param infile .rt file or 2nd argument
 * @return t_parser* 
 */
t_parser	*parse_input_file(char *infile)
{
	t_list		*tokens;
	t_parser	*input_data;

	tokens = NULL;
	tokenize_infile(infile, &tokens);
	input_data = parse_tokens(tokens);
	ft_lstclear(&tokens, delete_tokens);
	return (input_data);
}
