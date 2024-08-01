/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_plane.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 00:30:09 by hshimizu          #+#    #+#             */
/*   Updated: 2024/08/01 19:13:31 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects/plane.h"
#include "parser.h"
#include "rt_errno.h"
#include <stdlib.h>

static t_rt_errno	internal(t_parser_ctx *ctx, t_plane_init *args);

t_rt_errno	parse_plane(t_parser_ctx *ctx)
{
	t_rt_errno		ret;
	t_plane_init	args;
	t_plane			*tmp;

	ret = internal(ctx, &args);
	if (ret)
		return (ret);
	tmp = malloc(sizeof(*tmp));
	if (!tmp)
		return (FAILED_ALLOCATE);
	ret = plane_init(tmp, &args);
	if (ret)
		return (free(tmp), ret);
	if (ft_xlstinsert(&ctx->figures, 0, &tmp, sizeof(tmp)))
		return (((t_abstract_figure *)tmp)->_->del((t_abstract_figure *)tmp), \
			free(tmp), FAILED_ALLOCATE);
	return (SUCCESS);
}

static t_rt_errno	internal(t_parser_ctx *ctx, t_plane_init *args)
{
	const t_parse_entry	entries[] = {
	{NULL, (void *)parse_vec3, &args->coord},
	{NULL, (void *)parse_norm_vec3, &args->orient},
	{NULL, (void *)parse_color, &args->color},
	{"reflectivity", (void *)parse_decimal, &args->reflectivity},
	{"checker", (void *)parse_color, &args->checker},
	};
	static const size_t	size = sizeof(entries) / sizeof(*entries);

	*args = (t_plane_init){};
	return (parse_entries(ctx, entries, size));
}
