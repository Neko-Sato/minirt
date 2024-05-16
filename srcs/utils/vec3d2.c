/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3d2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 06:05:30 by hshimizu          #+#    #+#             */
/*   Updated: 2024/05/16 09:44:11 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils/vec3d.h"
#include <math.h>

long double	vec3d_abs(t_vec3d vec)
{
	return (sqrtl(powl(vec._[0], 2) + powl(vec._[1], 2) + powl(vec._[2], 2)));
}

t_vec3d	vec3d_norm(t_vec3d vec)
{
	return (vec3d_mul(1 / vec3d_abs(vec), vec));
}
