/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_basic_1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 04:45:04 by hshimizu          #+#    #+#             */
/*   Updated: 2024/07/02 00:54:40 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "rt_errno.h"
#include "utils/vec3d.h"

t_rt_errno	parse_vec3d(char **str, t_vec3d *dst)
{
	t_rt_errno	ret;
	char		*s;
	int			i;
	float		tmp;

	s = *str;
	i = 0;
	while (1)
	{
		ret = parse_decimal(&s, &tmp);
		if (ret)
			return (ret);
		dst->_[i++] = tmp;
		if (i >= 3)
			break ;
		if (*s++ != ',')
			return (INCORRECT_FORMAT);
	}
	*str = s;
	return (SUCCESS);
}

t_rt_errno	parse_norm_vec3d(char **str, t_vec3d *dst)
{
	t_rt_errno	ret;
	t_vec3d		tmp;
	char		*s;

	s = *str;
	ret = parse_vec3d(&s, &tmp);
	if (ret)
		return (ret);
	if (tmp._[0] < -1. || 1. < tmp._[0] || tmp._[1] < -1. || 1. < tmp._[1]
		|| tmp._[2] < -1. || 1. < tmp._[2])
		return (INCORRECT_FORMAT);
	*dst = tmp;
	*str = s;
	return (SUCCESS);
}

t_rt_errno	parse_color(char **str, t_color *dst)
{
	t_rt_errno	ret;
	char		*s;
	int			i;
	int			tmp;

	s = *str;
	dst->raw = 0xff000000;
	i = 0;
	while (1)
	{
		ret = parse_unsigned(&s, &tmp);
		if (ret)
			return (ret);
		if (0xff < tmp)
			return (INCORRECT_FORMAT);
		dst->raw |= (tmp & 0xff) << ((3 - ++i) * 8);
		if (i >= 3)
			break ;
		if (*s++ != ',')
			return (INCORRECT_FORMAT);
	}
	*str = s;
	return (SUCCESS);
}
