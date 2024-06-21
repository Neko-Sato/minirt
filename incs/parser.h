/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 04:43:23 by hshimizu          #+#    #+#             */
/*   Updated: 2024/06/21 23:43:33 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

/*
	I glanced at bison and flex,
	but I couldn't figure it out at all! I could have just used ft_strtok_r,
	but the string made it this way!
*/

# include "objects/scene.h"
# include <stddef.h>

typedef int	(*t_parse_optional_fn)(char **str, void *value);

# define IDENTIFIER_NUM 8

typedef enum e_identifier
{
	identifier_A,
	identifier_C,
	identifier_L,
	identifier_sp,
	identifier_pl,
	identifier_cy,
	identifier_sq,
	identifier_tr,
}			t_identifier;

int			parse_blank(char **str);
int			parse_identifier(char **str, t_identifier *value);
int			parse_integer(char **str, int *value, int unsign);
int			parse_decimal(char **str, float *value, int unsign);
int			parse_string(char **str, char **value);

int			parse_vec3d(char **str, t_vec3d *value);
int			parse_color(char **str, t_color *value);
int			parse_rate(char **str, float *value);
int			parse_norm_vec3d(char **str, t_vec3d *value);
int			parse_text(char **str, char *buf, size_t buf_size);

int			parse_line(char **str, t_scene *scene);
int			parse_eol(char **str);
int			parse_object(char **str, t_scene *scene);
int			parse_optional(char **str, t_parse_optional_fn fun, void *value);
int			parse_figure_optional(char **str, t_figure *value);
int			parse_camera_optional(char **str, t_camera *value);

int			parse_ambient(char **str, t_scene *scene);
int			parse_camera(char **str, t_scene *scene);
int			parse_light(char **str, t_scene *scene);
int			parse_sphere(char **str, t_scene *scene);
int			parse_plane(char **str, t_scene *scene);
int			parse_cylinder(char **str, t_scene *scene);
int			parse_square(char **str, t_scene *scene);
int			parse_triangle(char **str, t_scene *scene);

#endif
