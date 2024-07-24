/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mat3x3_rotation.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 04:58:21 by hshimizu          #+#    #+#             */
/*   Updated: 2024/07/23 01:47:34 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils/mat3x3.h"
#include <math.h>

t_mat3x3	mat3x3_rotation_x(float n)
{
	const t_mat3x3	tmp = {{
	{1, 0, 0},
	{0, cos(n), -sin(n)},
	{0, sin(n), cos(n)}
	}};

	return (tmp);
}

t_mat3x3	mat3x3_rotation_y(float n)
{
	const t_mat3x3	tmp = {{
	{cos(n), 0, sin(n)},
	{0, 1, 0},
	{-sin(n), 0, cos(n)}
	}};

	return (tmp);
}

t_mat3x3	mat3x3_rotation_z(float n)
{
	const t_mat3x3	tmp = {{
	{cos(n), -sin(n), 0},
	{sin(n), cos(n), 0},
	{0, 0, 1}
	}};

	return (tmp);
}

t_mat3x3	mat3x3_rotation_rollpitchyaw(float roll, float pitch, float yaw)
{
	return (mat3x3_mul(mat3x3_mul(mat3x3_rotation_z(roll),
				mat3x3_rotation_x(pitch)), mat3x3_rotation_y(yaw)));
}

t_mat3x3	mat3x3_rotation_axis(float n, t_vec3 axis)
{
	const t_mat3x3	e = {{{1, 0, 0}, {0, 1, 0}, {0, 0, 1}}};
	const t_mat3x3	k = {{
	{0, -axis._[2], axis._[1]},
	{axis._[2], 0, -axis._[0]},
	{-axis._[1], axis._[0], 0}}};

	return (mat3x3_add(e, mat3x3_add(mat3x3_mul_scalar(sin(n), k),
				mat3x3_mul_scalar(1 - cos(n), mat3x3_mul(k, k)))));
}
