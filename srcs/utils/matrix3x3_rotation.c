/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix3x3_rotation.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 04:58:21 by hshimizu          #+#    #+#             */
/*   Updated: 2024/06/26 07:55:01 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils/matrix3x3.h"
#include <math.h>

t_matrix3x3	matrix3x3_rotation_x(float n)
{
	const t_matrix3x3	tmp = {{
	{1, 0, 0},
	{0, cos(n), -sin(n)},
	{0, sin(n), cos(n)}
	}};

	return (tmp);
}

t_matrix3x3	matrix3x3_rotation_y(float n)
{
	const t_matrix3x3	tmp = {{
	{cos(n), 0, sin(n)},
	{0, 1, 0},
	{-sin(n), 0, cos(n)}
	}};

	return (tmp);
}

t_matrix3x3	matrix3x3_rotation_z(float n)
{
	const t_matrix3x3	tmp = {{
	{cos(n), -sin(n), 0},
	{sin(n), cos(n), 0},
	{0, 0, 1}
	}};

	return (tmp);
}

t_matrix3x3	matrix3x3_rotation_rollpitchyaw(float roll, float pitch, float yaw)
{
	return (matrix3x3_mul(matrix3x3_mul(matrix3x3_rotation_z(roll),
				matrix3x3_rotation_x(pitch)), matrix3x3_rotation_y(yaw)));
}

t_matrix3x3	matrix3x3_rotation_axis(float n, t_vec3d axis)
{
	const t_matrix3x3	e = {{{1, 0, 0}, {0, 1, 0}, {0, 0, 1}}};
	const t_matrix3x3	k = {{
	{0, -axis._[2], axis._[1]},
	{axis._[2], 0, -axis._[0]},
	{-axis._[1], axis._[0], 0}}};

	return (matrix3x3_add(e, matrix3x3_add(matrix3x3_mul_scalar(sin(n), k),
				matrix3x3_mul_scalar(1 - cos(n), matrix3x3_mul(k, k)))));
}
