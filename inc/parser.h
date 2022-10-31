/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: sde-quai <sde-quai@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/27 11:48:55 by sde-quai      #+#    #+#                 */
/*   Updated: 2022/10/25 12:09:22 by sde-quai      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "utils.h"

typedef struct s_alight {
	float	a_rat;
	t_vec4	colors;
}				t_alight;

typedef struct s_camera {
	t_vec4	cord;
	t_vec4	norm;
	float	fov;
}				t_camera;

typedef struct s_ligth {
	t_vec4	cord;
	float	b_rat;
	t_vec4	colors;
}				t_light;

typedef struct s_sphere {
	t_vec4	center;
	float	d;
	t_vec4	colors;
}				t_sphere;

typedef struct s_plane {
	t_vec4	cord;
	t_vec4	norm;
	t_vec4	colors;
}				t_plane;

typedef struct s_cylinder {
	t_vec4	cord;
	t_vec4	norm;
	float	d;
	float	h;
	t_vec4	colors;
	float	angle;
	t_vec4	k;
	float	zmin;
	float	zmax;
}				t_cylinder;

typedef struct s_parser
{
	t_alight	*al;
	t_camera	*cam;
	t_list		*l;
	t_list		*sphere;
	t_list		*plane;
	t_list		*cylinder;
}				t_parser;

// parser.c
t_parser	*parse_input_file(char *infile);

// tokens.c
void		tokenize_infile(char *infile, t_list **tokens);
void		delete_tokens(void *ct);

// p_utils.c
float		rt_atof(char *str);
t_parser	*init_parser(void);

// utils_vec.c
t_vec4		check_vec_is_norm(char *str);
t_vec4		check_and_fill_vec4(char *str);
t_vec4		check_vec_is_color(char *str);

// add_sources.c
void		fill_ambient_light(char **split, t_alight **al);
void		fill_light(char **split, t_list **lst);
void		fill_camera(char **split, t_camera **cam);

// add_objects.c
void		add_sphere(char **split, t_list **lst);
void		add_cylinder(char **split, t_list **lst);
void		add_plane(char **split, t_list **lst);

// free_input.c
void		free_input_data(t_parser *input_data);

#endif
