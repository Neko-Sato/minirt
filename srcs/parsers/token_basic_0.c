/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_basic_0.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 23:47:38 by hshimizu          #+#    #+#             */
/*   Updated: 2024/06/05 08:13:22 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "rt_errno.h"
#include <float.h>
#include <libft.h>
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

int	take_integer(char **str, long *value)
{
	char	*endptr;

	*value = ft_strtol(*str, &endptr, 10);
	if (endptr == *str)
		return (INCORRECT_FORMAT);
	*str = endptr;
	return (NO_ERROR);
}

int	take_decimal(char **str, double *value, int delta)
{
	char	*endptr;

	if (delta && ft_strchr("+-", (*str)[0]) && (*str)[1] == 'd')
	{
		if ((*str)[0] == '-')
			*value = -DBL_MIN;
		else 
			*value = DBL_MIN;
		*str += 2;
		return (NO_ERROR);
	}
	*value = ft_strtod(*str, &endptr);
	if (endptr == *str)
		return (INCORRECT_FORMAT);
	*str = endptr;
	return (NO_ERROR);
}
