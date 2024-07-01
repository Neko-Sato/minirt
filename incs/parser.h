/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 04:43:23 by hshimizu          #+#    #+#             */
/*   Updated: 2024/07/01 23:59:30 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "objects/scene.h"
# include "rt_errno.h"
# include <stddef.h>

typedef t_rt_errno			(*t_parse_fn)(char **str, void *dst);

//	Tokens
t_rt_errno					parse_integer(char **str, int *dst);
t_rt_errno					parse_unsigned(char **str, int *dst);
t_rt_errno					parse_decimal(char **str, float *dst);
t_rt_errno					parse_string(char **str, char **dst);
t_rt_errno					parse_vec3d(char **str, t_vec3d *dst);
t_rt_errno					parse_color(char **str, t_color *dst);
t_rt_errno					parse_norm_vec3d(char **str, t_vec3d *dst);

//	Utilities
typedef struct s_parse_entry
{
	t_parse_fn				fun;
	void					*dst;
}							t_parse_entry;

typedef struct s_parse_opt
{
	const char				*name;
	t_parse_fn				fun;
	void					*dst;
}							t_parse_opt;

t_rt_errno					parse_blank(char **str);
t_rt_errno					parse_text(char **str, char *buf, size_t size);
t_rt_errno					parse_entries(char **str,
								const t_parse_entry *entries, size_t size);
t_rt_errno					parse_optional(char **str,
								const t_parse_opt *entries, size_t size);

//	Parsers
t_rt_errno					parse_line(char **str, t_scene *scene);
t_rt_errno					parse_eol(char **str);

typedef struct s_identifier
{
	const char				*name;
	t_parse_fn				fun;
}							t_identifier;

extern const t_identifier	g_identifiers[];
extern const size_t			g_identifiers_size;

t_rt_errno					parse_object(char **str, t_scene *scene);
t_rt_errno					parse_identifier(char **str,
								const t_identifier **identifier);

t_rt_errno					parse_ambient(char **str, t_scene *scene);
t_rt_errno					parse_camera(char **str, t_scene *scene);
t_rt_errno					parse_light(char **str, t_scene *scene);
t_rt_errno					parse_sphere(char **str, t_scene *scene);
t_rt_errno					parse_plane(char **str, t_scene *scene);
t_rt_errno					parse_cylinder(char **str, t_scene *scene);
t_rt_errno					parse_square(char **str, t_scene *scene);
t_rt_errno					parse_triangle(char **str, t_scene *scene);

extern const t_figure_opt	g_default_figure_opt;

#endif
