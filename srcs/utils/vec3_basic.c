/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_basic.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 06:05:30 by hshimizu          #+#    #+#             */
/*   Updated: 2024/07/20 20:19:21 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils/vec3.h"
#include <math.h>

float	vec3_dot(t_vec3 a, t_vec3 b)
{
	return (a._[0] * b._[0] + a._[1] * b._[1] + a._[2] * b._[2]);
}

t_vec3	vec3_cross(t_vec3 a, t_vec3 b)
{
	t_vec3	result;

	result._[0] = a._[1] * b._[2] - a._[2] * b._[1];
	result._[1] = a._[2] * b._[0] - a._[0] * b._[2];
	result._[2] = a._[0] * b._[1] - a._[1] * b._[0];
	return (result);
}

float	vec3_abs(t_vec3 vec)
{
	return (sqrt(pow(vec._[0], 2) + pow(vec._[1], 2) + pow(vec._[2], 2)));
}

t_vec3	vec3_norm(t_vec3 vec)
{
	const float	size = vec3_abs(vec);

	if (size == 0.)
		return ((t_vec3){{0, 0, 0}});
	return (vec3_mul(1 / size, vec));
}

t_vec3	vec3_ortho(t_vec3 a, t_vec3 b)
{
	return (vec3_sub(b, vec3_mul(vec3_dot(a, b), a)));
}
