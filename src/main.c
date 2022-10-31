/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: sde-quai <sde-quai@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/27 10:08:56 by sde-quai      #+#    #+#                 */
/*   Updated: 2022/10/26 13:49:52 by sde-quai      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

/**
 * @brief Entry point of the program. test_input_file (in utils/verify_input.c)
 * parse_input_file (in parser/parser.c). The program can only run verified 
 * .rt files. For init_screen (init_screen.c) the .rt file is computed and put
 * to a window in the screen. free_input_data (parser/free_input.c) frees 
 * allocated memory.
 * 
 * @param argc
 * @param argv Valid .rt file 
 * @return int 
 */
int	main(int argc, char **argv)
{
	t_parser		*input_data;

	if (!test_input_file(argc, argv))
		return (EXIT_FAILURE);
	input_data = parse_input_file(argv[1]);
	init_screen(input_data);
	free_input_data(input_data);
	return (EXIT_SUCCESS);
}
