/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_square.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 00:30:09 by hshimizu          #+#    #+#             */
/*   Updated: 2024/07/02 00:15:40 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects/square.h"
#include "parser.h"
#include "rt_errno.h"
#include <stdlib.h>

static t_rt_errno	internal(char **str, t_square_init *args);

t_rt_errno	parse_square(char **str, t_scene *scene)
{
	t_rt_errno		ret;
	t_square_init	args;
	t_square		*tmp;

	ret = internal(str, &args);
	if (ret)
		return (ret);
	tmp = malloc(sizeof(*tmp));
	if (!tmp)
		return (FAILED_ALLOCATE);
	ret = square_init(tmp, &args);
	if (ret)
		return (free(tmp), ret);
	ret = scene_add_figure(scene, (t_figure *)tmp);
	if (ret)
		return (((t_figure *)tmp)->_->del((t_figure *)tmp), free(tmp), ret);
	return (SUCCESS);
}

static t_rt_errno	internal(char **str, t_square_init *args)
{
	const t_parse_entry	entries[] = {
	{(void *)parse_vec3d, &args->coord},
	{(void *)parse_norm_vec3d, &args->orient},
	{(void *)parse_decimal, &args->size},
	{(void *)parse_color, &args->color},
	};
	const t_parse_opt	opt[] = {
	{"reflectivity", (void *)parse_decimal, &args->opt.reflectivity},
	{"checker", (void *)parse_color, &args->opt.checker},
	{"bump", (void *)parse_string, &args->opt.bump},
	};
	static const size_t	size = sizeof(entries) / sizeof(*entries);
	static const size_t	opt_size = sizeof(opt) / sizeof(*opt);
	t_rt_errno			ret;

	args->opt = g_default_figure_opt;
	ret = parse_entries(str, entries, size);
	if (ret)
		return (ret);
	return (parse_optional(str, opt, opt_size));
}
