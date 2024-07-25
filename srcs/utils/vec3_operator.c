/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_basic.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 07:05:18 by hshimizu          #+#    #+#             */
/*   Updated: 2024/06/12 12:38:11 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils/vec3.h"
#include <math.h>

t_vec3	vec3_add(t_vec3 a, t_vec3 b)
{
	a._[0] += b._[0];
	a._[1] += b._[1];
	a._[2] += b._[2];
	return (a);
}

t_vec3	vec3_sub(t_vec3 a, t_vec3 b)
{
	a._[0] -= b._[0];
	a._[1] -= b._[1];
	a._[2] -= b._[2];
	return (a);
}

t_vec3	vec3_mul(float n, t_vec3 a)
{
	a._[0] *= n;
	a._[1] *= n;
	a._[2] *= n;
	return (a);
}