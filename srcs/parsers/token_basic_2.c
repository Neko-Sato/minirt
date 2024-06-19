/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_basic_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 04:45:04 by hshimizu          #+#    #+#             */
/*   Updated: 2024/06/19 16:14:10 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "rt_errno.h"
#include "utils/vec3d.h"
#include <libft.h>

int	parse_vec3d(char **str, t_vec3d *value)
{
	int		ret;
	char	*s;
	int		i;
	float	tmp;

	s = *str;
	i = 0;
	while (1)
	{
		ret = parse_decimal(&s, &tmp, 0);
		if (ret)
			return (ret);
		value->_[i++] = tmp;
		if (i >= 3)
			break ;
		if (*s++ != ',')
			return (INCORRECT_FORMAT);
	}
	*str = s;
	return (SUCCESS);
}

int	parse_color(char **str, t_color *value)
{
	int		ret;
	char	*s;
	int		i;
	int		tmp;

	s = *str;
	value->raw = 0xff000000;
	i = 0;
	while (1)
	{
		ret = parse_integer(&s, &tmp, 1);
		if (ret)
			return (ret);
		if (255 < tmp)
			return (OUT_OF_RANGE);
		value->raw |= (tmp & 0xff) << ((3 - ++i) * 8);
		if (i >= 3)
			break ;
		if (*s++ != ',')
			return (INCORRECT_FORMAT);
	}
	*str = s;
	return (SUCCESS);
}

int	parse_rate(char **str, float *value)
{
	int		ret;
	char	*s;

	s = *str;
	ret = parse_decimal(&s, value, 1);
	if (ret)
		return (ret);
	if (1. < *value)
		return (OUT_OF_RANGE);
	*str = s;
	return (SUCCESS);
}

int	parse_norm_vec3d(char **str, t_vec3d *value)
{
	int		ret;
	char	*s;

	s = *str;
	ret = parse_vec3d(&s, value);
	if (ret)
		return (ret);
	if (value->_[0] < -1. || 1. < value->_[0] || value->_[1] < -1.
		|| 1. < value->_[1] || value->_[2] < -1. || 1. < value->_[2])
		return (OUT_OF_RANGE);
	*str = s;
	return (SUCCESS);
}
