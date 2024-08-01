/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_triangle.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 00:30:09 by hshimizu          #+#    #+#             */
/*   Updated: 2024/08/01 20:22:36 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects/triangle.h"
#include "parser.h"
#include "rt_errno.h"
#include <stdlib.h>

static t_rt_errno	internal(t_parser_ctx *ctx, t_triangle_init *args);

t_rt_errno	parse_triangle(t_parser_ctx *ctx)
{
	t_rt_errno		ret;
	t_triangle_init	args;
	t_triangle		*tmp;

	ret = internal(ctx, &args);
	if (ret)
		return (ret);
	tmp = malloc(sizeof(*tmp));
	if (!tmp)
		return (FAILED_ALLOCATE);
	ret = triangle_init(tmp, &args);
	if (ret)
		return (free(tmp), ret);
	if (ft_xlstinsert(&ctx->figures, 0, &tmp, sizeof(tmp)))
		return (((t_abstract_figure *)tmp)->_->del((t_abstract_figure *)tmp), \
			free(tmp), FAILED_ALLOCATE);
	return (SUCCESS);
}

static t_rt_errno	internal(t_parser_ctx *ctx, t_triangle_init *args)
{
	const t_parse_entry	entries[] = {
	{NULL, (void *)parse_vec3, &args->first},
	{NULL, (void *)parse_vec3, &args->second},
	{NULL, (void *)parse_vec3, &args->third},
	{NULL, (void *)parse_color, &args->color},
	{"reflectivity", (void *)parse_decimal, &args->reflectivity},
	{"checker", (void *)parse_color, &args->checker},
	};
	static const size_t	size = sizeof(entries) / sizeof(*entries);

	*args = (t_triangle_init){};
	return (parse_entries(ctx, entries, size));
}
