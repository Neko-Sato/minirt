/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3d2_1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 06:05:30 by hshimizu          #+#    #+#             */
/*   Updated: 2024/06/12 12:38:18 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils/vec3d.h"
#include <math.h>

float	vec3d_dot(t_vec3d a, t_vec3d b)
{
	return (a._[0] * b._[0] + a._[1] * b._[1] + a._[2] * b._[2]);
}

t_vec3d	vec3d_cross(t_vec3d a, t_vec3d b)
{
	t_vec3d	result;

	result._[0] = a._[1] * b._[2] - a._[2] * b._[1];
	result._[1] = a._[2] * b._[0] - a._[0] * b._[2];
	result._[2] = a._[0] * b._[1] - a._[1] * b._[0];
	return (result);
}

float	vec3d_abs(t_vec3d vec)
{
	return (sqrtf(powl(vec._[0], 2) + powf(vec._[1], 2) + powf(vec._[2], 2)));
}

t_vec3d	vec3d_norm(t_vec3d vec)
{
	return (vec3d_mul(1 / vec3d_abs(vec), vec));
}
