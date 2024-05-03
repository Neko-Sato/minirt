/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_entry1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 07:27:42 by hshimizu          #+#    #+#             */
/*   Updated: 2024/05/03 09:57:00 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_error.h"
#include "vec3d.h"
#include <libft.h>

int	parse_vec3d(char *str, t_vec3d *vec)
{
	t_vec3d_array	vec_tmp;
	int				i;
	char			*token;
	char			*endptr;
	double			tmp;

	i = 0;
	while (i < 3)
	{
		token = ft_strsep(&str, ",");
		if (!token)
			return (INCORRECT_FORMAT);
		tmp = ft_strtod(token, &endptr);
		if (*endptr)
			return (INCORRECT_FORMAT);
		vec_tmp.array[i++] = tmp;
	}
	if (str)
		return (INCORRECT_FORMAT);
	*vec = vec_tmp.value;
	return (NO_ERROR);
}

int	parse_normalized_vec3d(char *str, t_vec3d *vec)
{
	t_vec3d	vec_tmp;

	if (parse_vec3d(str, &vec_tmp))
		return (INCORRECT_FORMAT);
	if ((vec_tmp.x < -1. || 1. < vec_tmp.x) || (vec_tmp.y < -1.
			|| 1. < vec_tmp.y) || (vec_tmp.z < -1. || 1. < vec_tmp.z))
		return (INCORRECT_FORMAT);
	*vec = vec3d_normalize(vec_tmp);
	return (NO_ERROR);
}

int	parse_color(char *str, int *color)
{
	int		color_tmp;
	int		i;
	char	*token;
	char	*endptr;
	long	tmp;

	color_tmp = 0;
	i = 0;
	while (i < 3)
	{
		token = ft_strsep(&str, ",");
		if (!token)
			return (INCORRECT_FORMAT);
		tmp = ft_strtol(token, &endptr, 10);
		if (*endptr || (tmp < 0 || 0xff < tmp))
			return (INCORRECT_FORMAT);
		color_tmp |= (tmp & 0xff) << (8 * i++);
	}
	if (str)
		return (INCORRECT_FORMAT);
	*color = color_tmp;
	return (NO_ERROR);
}
