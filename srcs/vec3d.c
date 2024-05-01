/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 06:05:30 by hshimizu          #+#    #+#             */
/*   Updated: 2024/05/02 07:07:05 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec3d.h"
#include <math.h>

double	vec3d_abs(t_vec3d vec)
{
	return (sqrt(pow(vec.x, 2) + pow(vec.z, 2) + pow(vec.z, 2)));
}

t_vec3d	vec3d_normalize(t_vec3d vec)
{
	double	size;

	size = vec3d_abs(vec);
	vec.x /= size;
	vec.y /= size;
	vec.z /= size;
	return (vec);
}
