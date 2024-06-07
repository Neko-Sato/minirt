/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_basic_0.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 23:47:38 by hshimizu          #+#    #+#             */
/*   Updated: 2024/06/08 04:40:11 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "rt_errno.h"
#include <libft.h>
#include <limits.h>
#include <stddef.h>

int	take_blank(char **str)
{
	char	*s;

	s = *str;
	while (ft_isblank(*s))
		s++;
	if (*str == s)
		return (INCORRECT_FORMAT);
	*str = s;
	return (NO_ERROR);
}

int	take_identifier(char **str, t_identifier *value)
{
	static const char *const	identifiers[] = {
		"A", "C", "L", "sp", "pl", "cy"};
	int							ret;
	char						*s;
	char						buf[5];
	int							i;

	s = *str;
	ret = take_text(&s, buf, 5);
	if (ret)
		return (ret);
	i = 0;
	while (i < IDENTIFIER_NUM && ft_strcmp(buf, identifiers[i]))
		i++;
	if (i >= IDENTIFIER_NUM)
		return (UNKNOW_IDENTIFIER);
	*value = i;
	*str = s;
	return (NO_ERROR);
}

int	take_integer(char **str, int *value)
{
	long	tmp;
	char	*endptr;

	tmp = ft_strtol(*str, &endptr, 10);
	if (endptr == *str)
		return (INCORRECT_FORMAT);
	if (tmp < INT_MIN || tmp > INT_MAX)
		return (OUT_OF_RANGE);
	*value = tmp;
	*str = endptr;
	return (NO_ERROR);
}

int	take_decimal(char **str, float *value, int delta)
{
	double	tmp;
	char	*endptr;

	if (delta && ft_strchr("+-", (*str)[0]) && (*str)[1] == 'd')
	{
		if ((*str)[0] == '-')
			*value = -__FLT_MIN__;
		else
			*value = __FLT_MIN__;
		*str += 2;
		return (NO_ERROR);
	}
	tmp = (float)ft_strtod(*str, &endptr);
	if (endptr == *str)
		return (INCORRECT_FORMAT);
	if (tmp < -__FLT_MAX__ || __FLT_MAX__ < tmp)
		return (OUT_OF_RANGE);
	*value = tmp;
	*str = endptr;
	return (NO_ERROR);
}
