/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix3x3_rotation.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 04:58:21 by hshimizu          #+#    #+#             */
/*   Updated: 2024/06/09 18:13:15 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils/matrix3x3.h"
#include <math.h>

t_matrix3x3	matrix3x3_rotation_x(float n)
{
	const t_matrix3x3	tmp = {{
	{1, 0, 0},
	{0, cosf(n), -sinf(n)},
	{0, sinf(n), cosf(n)}
	}};

	return (tmp);
}

t_matrix3x3	matrix3x3_rotation_y(float n)
{
	const t_matrix3x3	tmp = {{
	{cosf(n), 0, sinf(n)},
	{0, 1, 0},
	{-sinf(n), 0, cosf(n)}
	}};

	return (tmp);
}

t_matrix3x3	matrix3x3_rotation_z(float n)
{
	const t_matrix3x3	tmp = {{
	{cosf(n), -sinf(n), 0},
	{sinf(n), cosf(n), 0},
	{0, 0, 1}
	}};

	return (tmp);
}

t_matrix3x3	matrix3x3_rotation_axis(float n, t_vec3d axis)
{
	const float			cos_n = cosf(n);
	const float			_cos_n = 1 - cos_n;
	const float			sin_n = sinf(n);
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
