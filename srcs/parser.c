/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 01:37:56 by hshimizu          #+#    #+#             */
/*   Updated: 2024/05/16 10:00:25 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <limits.h>

int	parser(char *str, const t_parser_entry entries[], size_t size, void *value)
{
	int		ret;
	char	*token;
	size_t	i;

	i = 0;
	while (i < size)
	{
		token = ft_strsep(&str, RT_DELIMIITER);
		if (!token)
			return (INCORRECT_FORMAT);
		ret = entries[i].fun(token, (unsigned char *)value
				+ entries[i].dest_offset);
		if (ret)
			return (ret);
		i++;
	}
	token = ft_strsep(&str, RT_DELIMIITER);
	if (token)
		return (INCORRECT_FORMAT);
	return (NO_ERROR);
}

int	parse_int(char *str, int *value)
{
	long	tmp;
	char	*endptr;

	tmp = ft_strtol(str, &endptr, 10);
	if (*endptr || tmp < (long)INT_MIN || (long)INT_MAX < tmp)
		return (INCORRECT_FORMAT);
	*value = (int)tmp;
	return (NO_ERROR);
}

int	parse_dobule(char *str, double *value)
{
	double	tmp;
	char	*endptr;

	tmp = ft_strtod(str, &endptr);
	if (*endptr)
		return (INCORRECT_FORMAT);
	*value = tmp;
	return (NO_ERROR);
}

int	parse_vec3d(char *str, t_vec3d *value)
{
	t_vec3d	tmp;
	char	*token;
	char	*endptr;
	int		i;

	i = 0;
	while (i < 3)
	{
		token = ft_strsep(&str, ",");
		if (!token)
			return (INCORRECT_FORMAT);
		tmp._[i] = ft_strtod(token, &endptr);
		if (*endptr)
			return (INCORRECT_FORMAT);
		i++;
	}
	token = ft_strsep(&str, ",");
	if (token)
		return (INCORRECT_FORMAT);
	*value = tmp;
	return (NO_ERROR);
}
