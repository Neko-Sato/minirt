/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 07:05:18 by hshimizu          #+#    #+#             */
/*   Updated: 2024/05/16 09:44:05 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils/vec3d.h"
#include <math.h>

t_vec3d	vec3d_add(t_vec3d a, t_vec3d b)
{
	a._[0] += b._[0];
	a._[1] += b._[1];
	a._[2] += b._[2];
	return (a);
}

t_vec3d	vec3d_sub(t_vec3d a, t_vec3d b)
{
	a._[0] -= b._[0];
	a._[1] -= b._[1];
	a._[2] -= b._[2];
	return (a);
}

t_vec3d	vec3d_mul(long double n, t_vec3d a)
{
	a._[0] *= n;
	a._[1] *= n;
	a._[2] *= n;
	return (a);
}

long double	vec3d_dot(t_vec3d a, t_vec3d b)
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
