/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_ambient.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 16:21:28 by hshimizu          #+#    #+#             */
/*   Updated: 2024/07/14 03:58:01 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects/ambient.h"
#include "parser.h"
#include "constants.h"
#include "rt_errno.h"
#include <stdlib.h>
#include <libft.h>

static t_rt_errno	internal(char **str, t_ambient_init *args);

t_rt_errno	parse_ambient(char **str, t_parser *context)
{
	t_rt_errno		ret;
	t_ambient_init	args;
	t_ambient		*tmp;

	if (!ALLOW_MULTIPLE_AMIBIENTS && context->flag & AMBIENT_DEFINED)
		return (MULTIPLE_DEFINED_AMBIENT);
	ret = internal(str, &args);
	if (ret)
		return (ret);
	tmp = malloc(sizeof(*tmp));
	if (!tmp)
		return (FAILED_ALLOCATE);
	ret = ambient_init(tmp, &args);
	if (ret)
		return (free(tmp), ret);
	if (ft_xlstappend(&context->lights, &tmp, sizeof(tmp)))
		return (((t_abstract_light *)tmp)->_->del((t_abstract_light *)tmp), \
				free(tmp), FAILED_ALLOCATE);
	context->flag |= AMBIENT_DEFINED;
	return (SUCCESS);
}

static t_rt_errno	internal(char **str, t_ambient_init *args)
{
	const t_parse_entry	entries[] = {
	{(void *)parse_decimal, &args->brightness},
	{(void *)parse_color, &args->color},
	};
	static const size_t	size = sizeof(entries) / sizeof(*entries);

	*args = (t_ambient_init){};
	return (parse_entries(str, entries, size));
}
