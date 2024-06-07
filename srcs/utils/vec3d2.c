/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3d2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 06:05:30 by hshimizu          #+#    #+#             */
/*   Updated: 2024/06/08 04:47:21 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils/vec3d.h"
#include <math.h>

float	vec3d_abs(t_vec3d vec)
{
	return (sqrtf(powl(vec._[0], 2) + powf(vec._[1], 2) + powf(vec._[2], 2)));
}

t_vec3d	vec3d_norm(t_vec3d vec)
{
	return (vec3d_mul(1 / vec3d_abs(vec), vec));
}
