/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_basic_0.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 23:47:38 by hshimizu          #+#    #+#             */
/*   Updated: 2024/07/02 00:27:01 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "rt_errno.h"
#include <libft.h>
#include <limits.h>

t_rt_errno	parse_integer(char **str, int *dst)
{
	long	tmp;
	char	*endptr;

	tmp = ft_strtol(*str, &endptr, 10);
	if (endptr == *str || tmp < INT_MIN || tmp > INT_MAX)
		return (INCORRECT_FORMAT);
	*dst = tmp;
	*str = endptr;
	return (SUCCESS);
}

t_rt_errno	parse_unsigned(char **str, int *dst)
{
	t_rt_errno	ret;
	char		*s;

	s = *str;
	if (!ft_isdigit(*s))
		return (INCORRECT_FORMAT);
	ret = parse_integer(&s, dst);
	if (ret)
		return (ret);
	*str = s;
	return (SUCCESS);
}

t_rt_errno	parse_decimal(char **str, float *dst)
{
	double	tmp;
	char	*endptr;

	tmp = ft_strtod(*str, &endptr);
	if (endptr == *str)
		return (INCORRECT_FORMAT);
	*dst = tmp;
	*str = endptr;
	return (SUCCESS);
}

static t_rt_errno	parse_string_internal(char **str, t_strgen *strgen);

t_rt_errno	parse_string(char **str, char **dst)
{
	t_rt_errno	ret;
	t_strgen	*strgen;

	strgen = ft_strgennew(STRGEN_BUUFERSIZE);
	if (!strgen)
		return (FAILED_ALLOCATE);
	ret = parse_string_internal(str, strgen);
	if (!ret)
	{
		*dst = ft_strgencomp(strgen);
		if (!*dst)
			ret = FAILED_ALLOCATE;
	}
	ft_strgendel(strgen);
	return (ret);
}

static t_rt_errno	parse_string_internal(char **str, t_strgen *strgen)
{
	char	*s;

	s = *str;
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
	*str = s;
	return (SUCCESS);
}
