/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 07:30:25 by hshimizu          #+#    #+#             */
/*   Updated: 2024/05/03 12:42:59 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include <stddef.h>
# include <vec3d.h>

typedef int				(*t_parse_fun)(char *str, void *value);

typedef struct s_parse_entry
{
	size_t				dst_offset;
	t_parse_fun			parse_fun;
}						t_parse_entry;

typedef struct s_parse
{
	const char			*identifier;
	const t_parse_entry	*entry;
	size_t				size;
}						t_parse;

typedef struct s_object	t_object;

int						parse(char *str, t_object *object);

int						parse_vec3d(char *str, t_vec3d *vec);
int						parse_normalized_vec3d(char *str, t_vec3d *vec);
int						parse_color(char *str, int *color);
int						parse_ratio(char *str, double *ratio);
int						parse_fov(char *str, int *fov);
int						parse_double(char *str, double *value);

#endif
