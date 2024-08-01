/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_cylinder.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 00:58:15 by hshimizu          #+#    #+#             */
/*   Updated: 2024/08/01 22:36:15 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects/cylinder.h"
#include "parser.h"
#include "rt_errno.h"
#include <stdlib.h>
#include <libft.h>

static t_rt_errno	internal(t_parser_ctx *ctx, t_cylinder_init *args);

t_rt_errno	parse_cylinder(t_parser_ctx *ctx)
{
	t_rt_errno		ret;
	t_cylinder_init	args;
	t_cylinder		*tmp;

	ret = internal(ctx, &args);
	if (ret)
		return (ret);
	tmp = malloc(sizeof(*tmp));
	if (!tmp)
		return (FAILED_ALLOCATE);
	ret = cylinder_init(tmp, &args);
	if (ret)
		return (free(tmp), ret);
	if (ft_xlstinsert(&ctx->figures, 0, &tmp, sizeof(tmp)))
		return (((t_abstract_figure *)tmp)->_->del((t_abstract_figure *)tmp), \
			free(tmp), FAILED_ALLOCATE);
	return (SUCCESS);
}

static t_rt_errno	internal(t_parser_ctx *ctx, t_cylinder_init *args)
{
	const t_parse_entry	entries[] = {
	{NULL, (void *)parse_vec3, &args->coord},
	{NULL, (void *)parse_norm_vec3, &args->axis},
	{NULL, (void *)parse_decimal, &args->diameter},
	{NULL, (void *)parse_decimal, &args->height},
	{NULL, (void *)parse_color, &args->color},
	{"reflectivity", (void *)parse_decimal, &args->reflectivity},
	{"checker", (void *)parse_decimal, &args->checker},
	};
	static const size_t	size = sizeof(entries) / sizeof(*entries);

	*args = (t_cylinder_init){};
	return (parse_entries(ctx, entries, size));
}
