/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_light.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 00:17:18 by hshimizu          #+#    #+#             */
/*   Updated: 2024/07/14 03:21:03 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects/light.h"
#include "parser.h"
#include "constants.h"
#include "rt_errno.h"
#include <stdlib.h>
#include <libft.h>

static t_rt_errno	internal(char **str, t_light_init *args);

t_rt_errno	parse_light(char **str, t_parser *context)
{
	t_rt_errno		ret;
	t_light_init	args;
	t_light			*tmp;

	if (!ALLOW_MULTIPLE_LIGHTS && context->flag & LIGHT_DEFINED)
		return (MULTIPLE_DEFINED_LIGHT);
	ret = internal(str, &args);
	if (ret)
		return (ret);
	tmp = malloc(sizeof(*tmp));
	if (!tmp)
		return (FAILED_ALLOCATE);
	ret = light_init(tmp, &args);
	if (ret)
		return (free(tmp), ret);
	if (ft_xlstappend(&context->lights, &tmp, sizeof(tmp)))
		return (((t_abstract_light *)tmp)->_->del((t_abstract_light *)tmp), \
				free(tmp), FAILED_ALLOCATE);
	context->flag |= LIGHT_DEFINED;
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

	*args = (t_light_init){};
	return (parse_entries(str, entries, size));
}
