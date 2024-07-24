/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_sphere.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 00:30:09 by hshimizu          #+#    #+#             */
/*   Updated: 2024/07/24 07:28:59 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects/sphere.h"
#include "parser.h"
#include "rt_errno.h"
#include <stdlib.h>

static t_rt_errno	internal(char **str, t_sphere_init *args);

t_rt_errno	parse_sphere(char **str, t_parser *context)
{
	t_rt_errno		ret;
	t_sphere_init	args;
	t_sphere		*tmp;

	ret = internal(str, &args);
	if (ret)
		return (ret);
	tmp = malloc(sizeof(*tmp));
	if (!tmp)
		return (FAILED_ALLOCATE);
	ret = sphere_init(tmp, &args);
	if (ret)
		return (free(tmp), ret);
	if (ft_xlstappend(&context->figures, &tmp, sizeof(tmp)))
		return (((t_abstract_figure *)tmp)->_->del((t_abstract_figure *)tmp), \
			free(tmp), FAILED_ALLOCATE);
	return (SUCCESS);
}

static t_rt_errno	internal(char **str, t_sphere_init *args)
{
	const t_parse_entry	entries[] = {
	{(void *)parse_vec3, &args->coord},
	{(void *)parse_decimal, &args->diameter},
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

	*args = (t_sphere_init){};
	ret = parse_entries(str, entries, size);
	if (ret)
		return (ret);
	return (parse_optional(str, opt, opt_size));
}
