/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   methods_1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 19:07:39 by hshimizu          #+#    #+#             */
/*   Updated: 2024/07/24 11:47:54 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects/abstract_figure.h"
#include "objects/triangle.h"
#include "utils/vec3.h"
#include "constants.h"
#include <math.h>

int	triangle_intersect(t_triangle *self, const t_ray *ray, float max_dist,
		float *dist)
{
	t_abstract_figure *const	figure = (void *)self;
	t_ray						local_ray;
	float						k;
	t_vec3						tmp;

	if (!aabb_contains(&figure->aabb, ray, max_dist))
		return (0);
	local_ray = (t_ray){
		mat3x3_mul_vec3(figure->rotation_inv, ray->o),
		mat3x3_mul_vec3(figure->rotation_inv,
			vec3_sub(ray->c, figure->position))
	};
	k = -local_ray.c._[2] / local_ray.o._[2];
	if (k < MIN_DIST || max_dist < k)
		return (0);
	tmp = vec3_add(local_ray.c, vec3_mul(k, local_ray.o));
	if (tmp._[0] < 0 || tmp._[1] < 0 || 1 < tmp._[0] + tmp._[1])
		return (0);
	*dist = k;
	return (1);
}
