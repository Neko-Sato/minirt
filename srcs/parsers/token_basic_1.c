/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_basic_1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 04:45:04 by hshimizu          #+#    #+#             */
/*   Updated: 2024/08/01 19:31:55 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "rt_errno.h"
#include "utils/vec3.h"
#include <math.h>

t_rt_errno	parse_vec3(t_parser_ctx *ctx, t_vec3 *dst)
{
	t_rt_errno	ret;
	int			i;
	char		*s;
	float		tmp;

	s = ctx->str;
	i = 0;
	while (1)
	{
		ret = parse_decimal(ctx, &tmp);
		if (ret)
			return (ret);
		dst->_[i++] = tmp;
		if (i >= 3)
			break ;
		if (*ctx->str++ != ',')
		{
			ctx->str = s;
			return (INCORRECT_FORMAT);
		}
	}
	return (SUCCESS);
}

t_rt_errno	parse_norm_vec3(t_parser_ctx *ctx, t_vec3 *dst)
{
	t_rt_errno	ret;
	t_vec3		tmp;
	char		*s;

	s = ctx->str;
	ret = parse_vec3(ctx, &tmp);
	if (ret)
		return (ret);
	if (1. < fabs(tmp._[0]) || 1. < fabs(tmp._[1]) || 1. < fabs(tmp._[2]))
	{
		ctx->str = s;
		return (INCORRECT_FORMAT);
	}
	*dst = vec3_norm(tmp);
	return (SUCCESS);
}

t_rt_errno	parse_color(t_parser_ctx *ctx, t_color *dst)
{
	t_rt_errno	ret;
	char		*s;
	int			i;
	int			tmp;

	s = ctx->str;
	dst->raw = 0xff000000;
	i = 0;
	while (1)
	{
		ret = parse_unsigned(ctx, &tmp);
		if (ret)
			return (ret);
		if (0xff < tmp)
			return (INCORRECT_FORMAT);
		dst->raw |= (tmp & 0xff) << ((3 - ++i) * 8);
		if (i >= 3)
			break ;
		if (*ctx->str++ != ',')
		{
			ctx->str = s;
			return (INCORRECT_FORMAT);
		}
	}
	return (SUCCESS);
}
