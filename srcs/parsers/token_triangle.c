/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_triangle.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 00:30:09 by hshimizu          #+#    #+#             */
/*   Updated: 2024/07/14 03:22:04 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects/triangle.h"
#include "parser.h"
#include "rt_errno.h"
#include <stdlib.h>

static t_rt_errno	internal(char **str, t_triangle_init *args);

t_rt_errno	parse_triangle(char **str, t_parser *context)
{
	t_rt_errno		ret;
	t_triangle_init	args;
	t_triangle		*tmp;

	ret = internal(str, &args);
	if (ret)
		return (ret);
	tmp = malloc(sizeof(*tmp));
	if (!tmp)
		return (FAILED_ALLOCATE);
	ret = triangle_init(tmp, &args);
	if (ret)
		return (free(tmp), ret);
	if (ft_xlstappend(&context->figures, &tmp, sizeof(tmp)))
		return (((t_abstract_figure *)tmp)->_->del((t_abstract_figure *)tmp), \
			free(tmp), FAILED_ALLOCATE);
	return (SUCCESS);
}

static t_rt_errno	internal(char **str, t_triangle_init *args)
{
	const t_parse_entry	entries[] = {
	{(void *)parse_vec3d, &args->first},
	{(void *)parse_vec3d, &args->second},
	{(void *)parse_vec3d, &args->third},
	{(void *)parse_color, &args->color},
	};
	const t_parse_opt	opt[] = {
	{"reflectivity", (void *)parse_decimal, &args->reflectivity},
	{"checker", (void *)parse_color, &args->checker},
	{"bump", (void *)parse_string, &args->bump},
	};
	static const size_t	size = sizeof(entries) / sizeof(*entries);
	static const size_t	opt_size = sizeof(opt) / sizeof(*opt);
	t_rt_errno			ret;

	*args = (t_triangle_init){};
	ret = parse_entries(str, entries, size);
	if (ret)
		return (ret);
	return (parse_optional(str, opt, opt_size));
}
