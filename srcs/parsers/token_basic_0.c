/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_basic_0.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 23:47:38 by hshimizu          #+#    #+#             */
/*   Updated: 2024/08/01 19:24:26 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "rt_errno.h"
#include <libft.h>
#include <limits.h>
#include <math.h>

t_rt_errno	parse_integer(t_parser_ctx *ctx, int *dst)
{
	long	tmp;
	char	*endptr;

	tmp = ft_strtol(ctx->str, &endptr, 10);
	if (endptr == ctx->str)
		return (INCORRECT_FORMAT);
	if (tmp < INT_MIN || tmp > INT_MAX)
		return (OUT_OF_RANGE);
	*dst = tmp;
	ctx->str = endptr;
	return (SUCCESS);
}

t_rt_errno	parse_unsigned(t_parser_ctx *ctx, int *dst)
{
	if (!ft_isdigit(*ctx->str))
		return (INCORRECT_FORMAT);
	return (parse_integer(ctx, dst));
}

t_rt_errno	parse_decimal(t_parser_ctx *ctx, float *dst)
{
	double	tmp;
	char	*endptr;

	tmp = ft_strtod(ctx->str, &endptr);
	if (endptr == ctx->str)
		return (INCORRECT_FORMAT);
	if (__FLT_MAX__ < fabs(tmp))
		return (OUT_OF_RANGE);
	*dst = tmp;
	ctx->str = endptr;
	return (SUCCESS);
}

static t_rt_errno	parse_string_internal(t_parser_ctx *ctx, t_strgen *strgen);

t_rt_errno	parse_string(t_parser_ctx *ctx, char **dst)
{
	t_rt_errno	ret;
	t_strgen	*strgen;

	strgen = ft_strgennew(STRGEN_BUUFERSIZE);
	if (!strgen)
		return (FAILED_ALLOCATE);
	ret = parse_string_internal(ctx, strgen);
	if (!ret)
	{
		*dst = ft_strgencomp(strgen);
		if (!*dst)
			ret = FAILED_ALLOCATE;
	}
	ft_strgendel(strgen);
	return (ret);
}

static t_rt_errno	parse_string_internal(t_parser_ctx *ctx, t_strgen *strgen)
{
	char	*s;

	s = ctx->str;
	if (*s++ != '"')
		return (INCORRECT_FORMAT);
	while (*s && *s != '"')
	{
		if (*s == '\\')
			if (*++s)
				break ;
		if (ft_strgenchr(strgen, *s++))
			return (FAILED_ALLOCATE);
	}
	if (*s++ != '\"')
		return (INCORRECT_FORMAT);
	ctx->str = s;
	return (SUCCESS);
}
