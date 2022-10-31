/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tokens.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: sde-quai <sde-quai@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/27 11:48:33 by sde-quai      #+#    #+#                 */
/*   Updated: 2022/10/18 09:54:24 by sde-quai      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

/**
 * @brief deletes tokens
 * 
 * @param ct 
 */
void	delete_tokens(void *ct)
{
	char	**split;

	if (!ct)
		return ;
	split = (char **)ct;
	if (split)
		ft_split_free(split);
}

/**
 * @brief Removes newline at the of the line and splits the line into a 
 * char ** whic his put in the content of the list.
 * 
 * @param line from .rt file
 * @param tokens 
 */
static void	line_to_token(char *line, t_list **tokens)
{
	char	**split;
	t_list	*new;
	char	*n_line;

	n_line = ft_strtrim(line, "\n");
	split = ft_split(n_line, ' ');
	ft_check_malloc(split);
	if (!split[0])
	{
		ft_split_free(split);
		free(n_line);
		return ;
	}
	if (split[0][0] == '#')
	{
		ft_split_free(split);
		free(n_line);
		return ;
	}
	new = ft_lstnew(split);
	ft_lstadd_back(tokens, new);
	free(n_line);
}

/**
 * @brief This functions uses get_next_line to retrieve the data from the .rt 
 * file. In line_to_token the line is put to tokens
 * 
 * @param infile .rt file
 * @param tokens empty token list
 */
void	tokenize_infile(char *infile, t_list **tokens)
{
	int		fd;
	char	*line;

	fd = open(infile, O_RDONLY);
	if (fd < 0 || fd > OPEN_MAX)
		exit_error_message("mini_rt: cannot open file\n", 1);
	line = get_next_line(fd);
	while (line)
	{
		if (line[0] != '\n')
			line_to_token(line, tokens);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
}
