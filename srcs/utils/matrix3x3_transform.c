/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix3x3_transform.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 02:18:10 by hshimizu          #+#    #+#             */
/*   Updated: 2024/07/14 05:24:58 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_errno.h"
#include "utils/matrix3x3.h"
#include <math.h>

t_matrix3x3	matrix3x3_transform(t_vec3d a, t_vec3d b)
{
	return (matrix3x3_rotation_axis(
			acos(vec3d_dot(a, b) / (vec3d_abs(a) * vec3d_abs(b))),
			vec3d_cross(a, b)));
}

int	matrix3x3_orientation(t_vec3d f, t_vec3d u, t_matrix3x3 *transform)
{
	t_vec3d	_f;
	t_vec3d	_r;
	t_vec3d	_u;

	_r = vec3d_norm(vec3d_cross(u, f));
	if (!vec3d_abs(_r))
		return (-1);
	_f = vec3d_norm(f);
	_u = vec3d_norm(vec3d_cross(f, _r));
	*transform = (t_matrix3x3){{
	{_r._[0], _u._[0], _f._[0]},
	{_r._[1], _u._[1], _f._[1]},
	{_r._[2], _u._[2], _f._[2]},
	}};
	return (0);
}
