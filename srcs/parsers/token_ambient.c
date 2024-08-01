/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_ambient.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 16:21:28 by hshimizu          #+#    #+#             */
/*   Updated: 2024/08/01 08:14:59 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "constants.h"
#include "objects/ambient.h"
#include "parser.h"
#include "rt_errno.h"
#include <libft.h>
#include <stdlib.h>

static t_rt_errno	internal(t_parser_ctx *ctx, t_ambient_init *args);

t_rt_errno	parse_ambient(t_parser_ctx *ctx)
{
	t_rt_errno		ret;
	t_ambient_init	args;
	t_ambient		*tmp;

	if (!ALLOW_MULTIPLE_AMIBIENTS && ctx->flag & AMBIENT_DEFINED)
		return (MULTIPLE_DEFINED_AMBIENT);
	ret = internal(ctx, &args);
	if (ret)
		return (ret);
	tmp = malloc(sizeof(*tmp));
	if (!tmp)
		return (FAILED_ALLOCATE);
	ret = ambient_init(tmp, &args);
	if (ret)
		return (free(tmp), ret);
	if (ft_xlstinsert(&ctx->lights, 0, &tmp, sizeof(tmp)))
		return (((t_abstract_light *)tmp)->_->del((t_abstract_light *)tmp),
			free(tmp), FAILED_ALLOCATE);
	ctx->flag |= AMBIENT_DEFINED;
	return (SUCCESS);
}

static t_rt_errno	internal(t_parser_ctx *ctx, t_ambient_init *args)
{
	const t_parse_entry	entries[] = {
	{NULL, (void *)parse_decimal, &args->brightness},
	{NULL, (void *)parse_color, &args->color},
	};
	static const size_t	size = sizeof(entries) / sizeof(*entries);

	*args = (t_ambient_init){};
	return (parse_entries(ctx, entries, size));
}
