/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mat3x3_transform.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 02:18:10 by hshimizu          #+#    #+#             */
/*   Updated: 2024/07/23 01:47:34 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_errno.h"
#include "utils/mat3x3.h"
#include <math.h>

t_mat3x3	mat3x3_transform(t_vec3 a, t_vec3 b)
{
	return (mat3x3_mul(\
		mat3x3_mul_scalar(\
			vec3_abs(b) / vec3_abs(a), \
			(t_mat3x3){{{1, 0, 0}, {0, 1, 0}, {0, 0, 1}}}),
		mat3x3_rotation_axis(\
			acos(vec3_dot(a, b) / (vec3_abs(a) * vec3_abs(b))), \
			vec3_cross(a, b)) \
		));
}

t_mat3x3	mat3x3_basis(t_vec3 r, t_vec3 u, t_vec3 f)
{
	return ((t_mat3x3){{
			{r._[0], u._[0], f._[0]},
			{r._[1], u._[1], f._[1]},
			{r._[2], u._[2], f._[2]},
		}});
}
