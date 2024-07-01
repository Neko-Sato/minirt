/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_ambient.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 16:21:28 by hshimizu          #+#    #+#             */
/*   Updated: 2024/07/01 23:53:34 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects/ambient.h"
#include "parser.h"
#include "rt_errno.h"
#include <stdlib.h>

static t_rt_errno	internal(char **str, t_ambient_init *args);

t_rt_errno	parse_ambient(char **str, t_scene *scene)
{
	t_rt_errno		ret;
	t_ambient_init	args;
	t_ambient		*tmp;

	ret = internal(str, &args);
	if (ret)
		return (ret);
	tmp = malloc(sizeof(*tmp));
	if (!tmp)
		return (FAILED_ALLOCATE);
	ret = ambient_init(tmp, &args);
	if (ret)
		return (free(tmp), ret);
	ret = scene_add_ambient(scene, tmp);
	if (ret)
		return (ambient_del(tmp), free(tmp), ret);
	return (SUCCESS);
}

static t_rt_errno	internal(char **str, t_ambient_init *args)
{
	const t_parse_entry	entries[] = {
	{(void *)parse_decimal, &args->ratio},
	{(void *)parse_color, &args->color},
	};
	static const size_t	size = sizeof(entries) / sizeof(*entries);

	return (parse_entries(str, entries, size));
}
