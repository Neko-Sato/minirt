/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 02:22:48 by hshimizu          #+#    #+#             */
/*   Updated: 2024/05/16 09:52:57 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static inline int	parse_color_hex(char *str, t_color *value);
static inline int	parse_color_dec(char *str, t_color *value);

int	parse_color(char *str, t_color *value)
{
	if (!ft_strncasecmp("0x", str, 2))
		return (parse_color_hex(str, value));
	else
		return (parse_color_dec(str, value));
}

static inline int	parse_color_hex(char *str, t_color *value)
{
	t_color	tmp;
	long	n;
	char	*endptr;

	n = ft_strtol(str, &endptr, 16);
	if (*endptr)
		return (INCORRECT_FORMAT);
	tmp.raw = (int)((n & 0xffffff) | 0xff000000);
	*value = tmp;
	return (NO_ERROR);
}

static inline int	parse_color_dec(char *str, t_color *value)
{
	t_color	tmp;
	long	n;
	char	*token;
	char	*endptr;
	int		i;

	i = 0;
	tmp.raw = 0xff000000;
	while (i < 3)
	{
		token = ft_strsep(&str, ",");
		if (!token)
			return (INCORRECT_FORMAT);
		n = ft_strtol(token, &endptr, 10);
		if (*endptr || n < 0 || 255 < n)
			return (INCORRECT_FORMAT);
		tmp.raw |= (n & 0xff) << (8 * (3 - i++));
	}
	token = ft_strsep(&str, ",");
	if (token)
		return (INCORRECT_FORMAT);
	*value = tmp;
	return (NO_ERROR);
}

int	parse_norm_vec3d(char *str, t_vec3d *value)
{
	int		ret;
	t_vec3d	tmp;

	ret = parse_vec3d(str, &tmp);
	if (ret)
		return (ret);
	if (tmp._[0] < -1.l || 1.l < tmp._[0] || tmp._[1] < -1.l || 1.l < tmp._[1]
		|| tmp._[2] < -1.l || 1.l < tmp._[2])
		return (INCORRECT_FORMAT);
	*value = tmp;
	return (NO_ERROR);
}

int	parse_rate(char *str, double *value)
{
	int		ret;
	double	tmp;

	ret = parse_dobule(str, &tmp);
	if (ret)
		return (ret);
	if (tmp < 0. || 1. < tmp)
		return (INCORRECT_FORMAT);
	*value = tmp;
	return (NO_ERROR);
}
