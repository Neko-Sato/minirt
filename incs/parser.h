/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 04:43:23 by hshimizu          #+#    #+#             */
/*   Updated: 2024/06/08 05:21:10 by hshimizu         ###   ########.fr       */
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

typedef int	(*t_take_optional_fn)(char **str, void *value);

# define IDENTIFIER_NUM 6

typedef enum e_identifier
{
	identifier_A,
	identifier_C,
	identifier_L,
	identifier_sp,
	identifier_pl,
	identifier_cy,
}			t_identifier;

int			take_blank(char **str);
int			take_identifier(char **str, t_identifier *value);
int			take_integer(char **str, int *value);
int			take_decimal(char **str, float *value, int delta);
int			take_string(char **str, char **value);

int			take_vec3d(char **str, t_vec3d *value, int delta);
int			take_color(char **str, t_color *value);
int			take_rate(char **str, float *value);
int			take_norm_vec3d(char **str, t_vec3d *value);
int			take_text(char **str, char *buf, size_t buf_size);

int			take_line(char **str, t_scene *scene);
int			take_eol(char **str);
int			take_object(char **str, t_scene *scene);
int			take_optional(char **str, t_take_optional_fn fun, void *value);
int			take_figure_optional(char **str, t_figure *value);
int			take_camera_optional(char **str, t_camera *value);

int			take_ambient(char **str, t_scene *scene);
int			take_camera(char **str, t_scene *scene);
int			take_light(char **str, t_scene *scene);
int			take_sphere(char **str, t_scene *scene);
int			take_plane(char **str, t_scene *scene);
int			take_cylinder(char **str, t_scene *scene);

#endif
