/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 04:43:23 by hshimizu          #+#    #+#             */
/*   Updated: 2024/08/01 22:12:59 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "objects/scene.h"
# include "rt_errno.h"
# include <libft.h>
# include <stddef.h>

# define CAMERA_DEFINED 0b001
# define AMBIENT_DEFINED 0b010
# define LIGHT_DEFINED 0b100

typedef struct s_parser_ctx
{
	const char				*filename;
	t_file					*stream;
	char					*line;
	size_t					line_size;
	size_t					lineno;
	char					*str;
	int						flag;
	t_xlst					*cameras;
	t_xlst					*lights;
	t_xlst					*figures;
}							t_parser_ctx;

typedef struct s_parser_res
{
	t_xlst					*cameras;
	t_xlst					*lights;
	t_xlst					*figures;
}							t_parser_res;

t_rt_errno					parser(const char *filename, t_parser_res *res);

typedef t_rt_errno			(*t_parse_fn)(t_parser_ctx *ctx);
typedef t_rt_errno			(*t_parse_r_fn)(t_parser_ctx *ctx, void *dst);

t_rt_errno					parse_integer(t_parser_ctx *ctx, int *dst);
t_rt_errno					parse_unsigned(t_parser_ctx *ctx, int *dst);
t_rt_errno					parse_decimal(t_parser_ctx *ctx, float *dst);
t_rt_errno					parse_string(t_parser_ctx *ctx, char **dst);
t_rt_errno					parse_vec3(t_parser_ctx *ctx, t_vec3 *dst);
t_rt_errno					parse_color(t_parser_ctx *ctx, t_color *dst);
t_rt_errno					parse_norm_vec3(t_parser_ctx *ctx, t_vec3 *dst);

typedef struct s_parse_entry
{
	const char				*name;
	t_parse_r_fn			fun;
	void					*dst;
}							t_parse_entry;

t_rt_errno					parse_blank(t_parser_ctx *ctx);
t_rt_errno					parse_text(t_parser_ctx *ctx, char *buf,
								size_t size);
t_rt_errno					parse_entry(t_parser_ctx *ctx,
								const t_parse_entry *entry);
t_rt_errno					parse_entries(t_parser_ctx *ctx,
								const t_parse_entry *entries, size_t size);

t_rt_errno					parse_line(t_parser_ctx *ctx);
t_rt_errno					parse_eol(t_parser_ctx *ctx);

typedef struct s_identifier
{
	const char				*name;
	t_parse_fn				fun;
}							t_identifier;

extern const t_identifier	g_identifiers[];
extern const size_t			g_identifiers_size;

t_rt_errno					parse_object(t_parser_ctx *ctx);
t_rt_errno					parse_identifier(t_parser_ctx *ctx,
								const t_identifier **identifier);

t_rt_errno					parse_ambient(t_parser_ctx *ctx);
t_rt_errno					parse_camera(t_parser_ctx *ctx);
t_rt_errno					parse_light(t_parser_ctx *ctx);
t_rt_errno					parse_sphere(t_parser_ctx *ctx);
t_rt_errno					parse_plane(t_parser_ctx *ctx);
t_rt_errno					parse_cylinder(t_parser_ctx *ctx);
t_rt_errno					parse_triangle(t_parser_ctx *ctx);
t_rt_errno					parse_cone(t_parser_ctx *ctx);

#endif
