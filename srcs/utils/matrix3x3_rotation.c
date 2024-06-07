/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix3x3_rotation.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 04:58:21 by hshimizu          #+#    #+#             */
/*   Updated: 2024/06/06 08:00:14 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils/matrix3x3.h"
#include <math.h>

t_matrix3x3	matrix3x3_rotation(long double x, long double y, long double z)
{
	const t_matrix3x3	a = {{
	{1, 0, 0},
	{0, cosl(x), -sinl(x)},
	{0, sinl(x), cosl(x)}
	}};
	const t_matrix3x3	b = {{
	{cosl(y), 0, sinl(y)},
	{0, 1, 0},
	{-sinl(y), 0, cosl(y)}
	}};
	const t_matrix3x3	c = {{
	{cosl(z), -sinl(z), 0},
	{sinl(z), cosl(z), 0},
	{0, 0, 1}
	}};

	return (matrix3x3_mul(matrix3x3_mul(a, b), c));
}

t_matrix3x3	matrix3x3_rotation_axis(long double n, t_vec3d axis)
{
	const long double	cos_n = cosl(n);
	const long double	_cos_n = 1 - cos_n;
	const long double	sin_n = sinl(n);
	const t_matrix3x3	tmp = {{
	{
		cos_n + axis._[0] * axis._[0] * _cos_n,
		axis._[0] * axis._[1] * _cos_n - axis._[2] * sin_n,
		axis._[2] * axis._[0] * _cos_n + axis._[1] * sin_n,
	},
	{
		axis._[0] * axis._[1] * _cos_n + axis._[2] * sin_n,
		cos_n + axis._[1] * axis._[1] * _cos_n,
		axis._[1] * axis._[2] * _cos_n - axis._[0] * sin_n,
	},
	{
		axis._[2] * axis._[0] * _cos_n - axis._[1] * sin_n,
		axis._[1] * axis._[2] * _cos_n + axis._[0] * sin_n,
		cos_n + axis._[2] * axis._[2] * _cos_n,
	},
	}};

	return (tmp);
}
