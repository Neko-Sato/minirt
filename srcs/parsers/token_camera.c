/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_camera.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 00:17:18 by hshimizu          #+#    #+#             */
/*   Updated: 2024/07/02 00:14:35 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects/camera.h"
#include "parser.h"
#include "rt_errno.h"
#include <math.h>
#include <stdlib.h>

static t_rt_errno	internal(char **str, t_camera_init *args);

t_rt_errno	parse_camera(char **str, t_scene *scene)
{
	t_rt_errno		ret;
	t_camera_init	args;
	t_camera		*tmp;

	ret = internal(str, &args);
	if (ret)
		return (ret);
	tmp = malloc(sizeof(*tmp));
	if (!tmp)
		return (FAILED_ALLOCATE);
	ret = camera_init(tmp, &args);
	if (ret)
		return (free(tmp), ret);
	ret = scene_add_camera(scene, tmp);
	if (ret)
		return (camera_del(tmp), free(tmp), ret);
	return (SUCCESS);
}

static t_rt_errno	internal(char **str, t_camera_init *args)
{
	const t_parse_entry	entries[] = {
	{(void *)parse_vec3d, &args->coord},
	{(void *)parse_norm_vec3d, &args->orient},
	{(void *)parse_integer, &args->fov},
	};
	static const size_t	size = sizeof(entries) / sizeof(*entries);
	const t_parse_opt	opt[] = {
	{"up", (void *)parse_norm_vec3d, &args->up},
	{"dist", (void *)parse_decimal, &args->dist},
	{"width", (void *)parse_unsigned, &args->width},
	{"height", (void *)parse_unsigned, &args->height},
	};
	static const size_t	opt_size = sizeof(opt) / sizeof(*opt);
	t_rt_errno			ret;

	args->up = (t_vec3d){{0, 1, 0}};
	args->dist = INFINITY;
	args->width = 1000;
	args->height = 800;
	ret = parse_entries(str, entries, size);
	if (ret)
		return (ret);
	return (parse_optional(str, opt, opt_size));
}
