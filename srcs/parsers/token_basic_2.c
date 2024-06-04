/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_basic_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 04:45:04 by hshimizu          #+#    #+#             */
/*   Updated: 2024/06/05 08:05:31 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "rt_errno.h"
#include "utils/vec3d.h"
#include <libft.h>

int	take_vec3d(char **str, t_vec3d *value, int delta)
{
	int		ret;
	char	*s;
	int		i;
	double	tmp;

	s = *str;
	i = 0;
	while (1)
	{
		ret = take_decimal(&s, &tmp, delta);
		if (ret)
			return (ret);
		value->_[i++] = tmp;
		if (i >= 3)
			break ;
		if (*s++ != ',')
			return (INCORRECT_FORMAT);
	}
	*str = s;
	return (NO_ERROR);
}

int	take_color(char **str, t_color *value)
{
	int		ret;
	char	*s;
	int		i;
	long	tmp;

	s = *str;
	value->raw = 0xff000000;
	i = 0;
	while (1)
	{
		ret = take_integer(&s, &tmp);
		if (tmp < 0 || 255 < tmp)
			return (OUT_OF_RANGE);
		if (ret)
			return (ret);
		value->raw |= (tmp & 0xff) << ((3 - i++) * 8);
		if (i >= 3)
			break ;
		if (*s++ != ',')
			return (INCORRECT_FORMAT);
	}
	*str = s;
	return (NO_ERROR);
}

int	take_rate(char **str, double *value)
{
	int		ret;
	char	*s;

	s = *str;
	ret = take_decimal(&s, value, 0);
	if (ret)
		return (ret);
	if (*value < 0. || 1. < *value)
		return (OUT_OF_RANGE);
	*str = s;
	return (NO_ERROR);
}

int	take_norm_vec3d(char **str, t_vec3d *value)
{
	int		ret;
	char	*s;

	s = *str;
	ret = take_vec3d(&s, value, 0);
	if (ret)
		return (ret);
	if (value->_[0] < -1.f || 1.f < value->_[0] || value->_[1] < -1.f
		|| 1.f < value->_[1] || value->_[2] < -1.f || 1.f < value->_[2])
		return (OUT_OF_RANGE);
	*str = s;
	return (NO_ERROR);
}
