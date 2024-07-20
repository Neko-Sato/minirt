/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix3x3_transform.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 02:18:10 by hshimizu          #+#    #+#             */
/*   Updated: 2024/07/20 20:45:06 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_errno.h"
#include "utils/matrix3x3.h"
#include <math.h>

t_matrix3x3	matrix3x3_transform(t_vec3d a, t_vec3d b)
{
	return (matrix3x3_mul(\
		matrix3x3_mul_scalar(\
			vec3d_abs(b) / vec3d_abs(a), \
			(t_matrix3x3){{{1, 0, 0}, {0, 1, 0}, {0, 0, 1}}}),
		matrix3x3_rotation_axis(\
			acos(vec3d_dot(a, b) / (vec3d_abs(a) * vec3d_abs(b))), \
			vec3d_cross(a, b)) \
		));
}

t_matrix3x3	matrix3x3_basis(t_vec3d r, t_vec3d u, t_vec3d f)
{
	return ((t_matrix3x3){{
			{r._[0], u._[0], f._[0]},
			{r._[1], u._[1], f._[1]},
			{r._[2], u._[2], f._[2]},
		}});
}
