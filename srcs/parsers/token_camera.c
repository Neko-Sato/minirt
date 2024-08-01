/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_camera.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 00:17:18 by hshimizu          #+#    #+#             */
/*   Updated: 2024/08/01 19:13:43 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects/camera.h"
#include "parser.h"
#include "constants.h"
#include "rt_errno.h"
#include <math.h>
#include <stdlib.h>
#include <libft.h>

static t_rt_errno	internal(t_parser_ctx *ctx, t_camera_init *args);

t_rt_errno	parse_camera(t_parser_ctx *ctx)
{
	t_rt_errno		ret;
	t_camera_init	args;
	t_camera		*tmp;

	if (!ALLOW_MULTIPLE_CAMERAS && ctx->flag & CAMERA_DEFINED)
		return (MULTIPLE_DEFINED_CAMERA);
	ret = internal(ctx, &args);
	if (ret)
		return (ret);
	tmp = malloc(sizeof(*tmp));
	if (!tmp)
		return (FAILED_ALLOCATE);
	ret = camera_init(tmp, &args);
	if (ret)
		return (free(tmp), ret);
	if (ft_xlstinsert(&ctx->cameras, 0, &tmp, sizeof(tmp)))
		return (camera_del(tmp), free(tmp), FAILED_ALLOCATE);
	ctx->flag |= CAMERA_DEFINED;
	return (SUCCESS);
}

static t_rt_errno	internal(t_parser_ctx *ctx, t_camera_init *args)
{
	const t_parse_entry	entries[] = {
	{NULL, (void *)parse_vec3, &args->coord},
	{NULL, (void *)parse_norm_vec3, &args->orient},
	{"up", (void *)parse_norm_vec3, &args->up},
	{NULL, (void *)parse_integer, &args->fov},
	{"width", (void *)parse_unsigned, &args->width},
	{"height", (void *)parse_unsigned, &args->height},
	};
	static const size_t	size = sizeof(entries) / sizeof(*entries);

	*args = (t_camera_init){};
	args->up = (t_vec3){{0, 1, 0}};
	args->width = 1000;
	args->height = 800;
	return (parse_entries(ctx, entries, size));
}
