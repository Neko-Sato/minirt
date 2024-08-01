/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 19:23:41 by hshimizu          #+#    #+#             */
/*   Updated: 2024/08/01 21:24:09 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "rt_errno.h"
#include <libft.h>

t_rt_errno	parse_line(t_parser_ctx *ctx)
{
	t_rt_errno	ret;

	ret = parse_blank(ctx);
	if (ret != SUCCESS && ret != INCORRECT_FORMAT)
		return (ret);
	ret = parse_eol(ctx);
	if (ret == INCORRECT_FORMAT)
	{
		ret = parse_object(ctx);
		if (ret)
			return (ret);
		ret = parse_blank(ctx);
		if (ret != SUCCESS && ret != INCORRECT_FORMAT)
			return (ret);
		ret = parse_eol(ctx);
	}
	return (ret);
}

t_rt_errno	parse_eol(t_parser_ctx *ctx)
{
	if (!ft_strchr("#\n", *ctx->str))
		return (INCORRECT_FORMAT);
	while (*ctx->str)
		ctx->str++;
	return (SUCCESS);
}

t_rt_errno	parse_object(t_parser_ctx *ctx)
{
	t_rt_errno			ret;
	const t_identifier	*identifier;

	ret = parse_identifier(ctx, &identifier);
	if (ret)
		return (ret);
	return (identifier->fun(ctx));
}

const t_identifier	g_identifiers[] = {
{"A", (void *)parse_ambient},
{"C", (void *)parse_camera},
{"L", (void *)parse_light},
{"sp", (void *)parse_sphere},
{"pl", (void *)parse_plane},
{"cy", (void *)parse_cylinder},
{"tr", (void *)parse_triangle},
{"cn", (void *)parse_cone},
};

const size_t		g_identifiers_size = \
	sizeof(g_identifiers) / sizeof(*g_identifiers);

t_rt_errno	parse_identifier(t_parser_ctx *ctx, const t_identifier **identifier)
{
	t_rt_errno	ret;
	char		buf[3];
	size_t		i;

	ret = parse_text(ctx, buf, sizeof(buf));
	if (ret)
		return (ret);
	i = 0;
	while (i < g_identifiers_size)
	{
		if (!ft_strcmp(g_identifiers[i].name, buf))
			break ;
		i++;
	}
	if (g_identifiers_size <= i)
		return (UNKNOW_IDENTIFIER);
	*identifier = &g_identifiers[i];
	return (SUCCESS);
}
