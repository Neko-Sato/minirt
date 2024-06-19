/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_basic_0.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 23:47:38 by hshimizu          #+#    #+#             */
/*   Updated: 2024/06/19 16:14:10 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "rt_errno.h"
#include <libft.h>
#include <limits.h>
#include <math.h>
#include <stddef.h>

int	parse_blank(char **str)
{
	char	*s;

	s = *str;
	while (ft_isblank(*s))
		s++;
	if (*str == s)
		return (INCORRECT_FORMAT);
	*str = s;
	return (SUCCESS);
}

int	parse_identifier(char **str, t_identifier *value)
{
	static const char *const	identifiers[] = {
		"A", "C", "L", "sp", "pl", "cy", "sq", "tr"};
	int							ret;
	char						*s;
	char						buf[5];
	int							i;

	s = *str;
	ret = parse_text(&s, buf, 5);
	if (ret)
		return (ret);
	i = 0;
	while (i < IDENTIFIER_NUM && ft_strcmp(buf, identifiers[i]))
		i++;
	if (i >= IDENTIFIER_NUM)
		return (UNKNOW_IDENTIFIER);
	*value = i;
	*str = s;
	return (SUCCESS);
}

int	parse_integer(char **str, int *value, int unsign)
{
	long	tmp;
	char	*endptr;

	tmp = ft_strtol(*str, &endptr, 10);
	if (endptr == *str)
		return (INCORRECT_FORMAT);
	if (tmp < INT_MIN || tmp > INT_MAX)
		return (OUT_OF_RANGE);
	if (unsign && tmp < 0)
		return (OUT_OF_RANGE);
	*value = tmp;
	*str = endptr;
	return (SUCCESS);
}

int	parse_decimal(char **str, float *value, int unsign)
{
	double	tmp;
	char	*endptr;

	if (ft_strchr("+-", (*str)[0]) && (*str)[1] == 'd')
	{
		if ((*str)[0] == '-')
			*value = -__FLT_MIN__;
		else
			*value = __FLT_MIN__;
		endptr = *str + 2;
	}
	else
	{
		tmp = (float)ft_strtod(*str, &endptr);
		if (endptr == *str)
			return (INCORRECT_FORMAT);
		*value = tmp;
	}
	if ((unsign && *value < 0) || isnan(*value))
		return (OUT_OF_RANGE);
	*str = endptr;
	return (SUCCESS);
}
