/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_light.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 00:17:18 by hshimizu          #+#    #+#             */
/*   Updated: 2024/07/02 00:15:18 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects/light.h"
#include "parser.h"
#include "rt_errno.h"
#include <stdlib.h>

static t_rt_errno	internal(char **str, t_light_init *args);

t_rt_errno	parse_light(char **str, t_scene *scene)
{
	t_rt_errno		ret;
	t_light_init	args;
	t_light			*tmp;

	ret = internal(str, &args);
	if (ret)
		return (ret);
	tmp = malloc(sizeof(*tmp));
	if (!tmp)
		return (FAILED_ALLOCATE);
	ret = light_init(tmp, &args);
	if (ret)
		return (free(tmp), ret);
	ret = scene_add_light(scene, tmp);
	if (ret)
		return (light_del(tmp), free(tmp), ret);
	return (SUCCESS);
}

static t_rt_errno	internal(char **str, t_light_init *args)
{
	const t_parse_entry		entries[] = {
	{(void *)parse_vec3d, &args->coord},
	{(void *)parse_decimal, &args->brightness},
	{(void *)parse_color, &args->color},
	};
	static const size_t		size = sizeof(entries) / sizeof(*entries);

	return (parse_entries(str, entries, size));
}
