/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_light.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 00:17:18 by hshimizu          #+#    #+#             */
/*   Updated: 2024/08/01 19:12:06 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects/light.h"
#include "parser.h"
#include "constants.h"
#include "rt_errno.h"
#include <stdlib.h>
#include <libft.h>

static t_rt_errno	internal(t_parser_ctx *ctx, t_light_init *args);

t_rt_errno	parse_light(t_parser_ctx *ctx)
{
	t_rt_errno		ret;
	t_light_init	args;
	t_light			*tmp;

	if (!ALLOW_MULTIPLE_LIGHTS && ctx->flag & LIGHT_DEFINED)
		return (MULTIPLE_DEFINED_LIGHT);
	ret = internal(ctx, &args);
	if (ret)
		return (ret);
	tmp = malloc(sizeof(*tmp));
	if (!tmp)
		return (FAILED_ALLOCATE);
	ret = light_init(tmp, &args);
	if (ret)
		return (free(tmp), ret);
	if (ft_xlstinsert(&ctx->lights, 0, &tmp, sizeof(tmp)))
		return (((t_abstract_light *)tmp)->_->del((t_abstract_light *)tmp), \
				free(tmp), FAILED_ALLOCATE);
	ctx->flag |= LIGHT_DEFINED;
	return (SUCCESS);
}

static t_rt_errno	internal(t_parser_ctx *ctx, t_light_init *args)
{
	const t_parse_entry		entries[] = {
	{NULL, (void *)parse_vec3, &args->coord},
	{NULL, (void *)parse_decimal, &args->brightness},
	{NULL, (void *)parse_color, &args->color},
	};
	static const size_t		size = sizeof(entries) / sizeof(*entries);

	*args = (t_light_init){};
	return (parse_entries(ctx, entries, size));
}
