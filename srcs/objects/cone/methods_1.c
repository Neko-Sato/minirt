/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   methods_1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 04:57:05 by hshimizu          #+#    #+#             */
/*   Updated: 2024/07/24 08:16:56 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects/abstract_figure.h"
#include "objects/cone.h"
#include "constants.h"
#include "utils/vec3.h"
#include "utils/ray.h"
#include "utils/mat3x3.h"
#include "utils/aabb.h"
#include <math.h>

static void	make_coeff(t_cone *self, const t_ray *ray, float coeff[3])
{
	t_abstract_figure *const	figure = (void *)self;
	const t_ray					local_ray = {
		mat3x3_mul_vec3(figure->rotation_inv, ray->o),
		mat3x3_mul_vec3(figure->rotation_inv,
			vec3_sub(ray->c, figure->position))
	};

	coeff[0] = (pow(local_ray.o._[0], 2) + pow(local_ray.o._[2], 2)
			- pow(local_ray.o._[1], 2));
	coeff[1] = 2 * (local_ray.o._[0] * local_ray.c._[0]
			+ local_ray.o._[2] * local_ray.c._[2]
			- local_ray.o._[1] * (local_ray.c._[1] - 1));
	coeff[2] = pow(local_ray.c._[0], 2) + pow(local_ray.c._[2], 2)
		- pow(local_ray.c._[1] - 1, 2);
}

static inline int	check_height(t_cone *self, const t_ray *ray, float k)
{
	t_abstract_figure *const	figure = (void *)self;
	const float					height = \
	mat3x3_mul_vec3(figure->rotation_inv, vec3_sub(\
		vec3_add(vec3_mul(k, ray->o), ray->c), figure->position))._[1];

	return (height < 0 || 1 < height);
}

int	cone_intersect(t_cone *self, const t_ray *ray, float max_dist,
		float *dist)
{
	t_abstract_figure *const	figure = (void *)self;
	float						coeff[3];
	float						tmp;
	float						k;

	if (!aabb_contains(&figure->aabb, ray, max_dist))
		return (0);
	make_coeff(self, ray, coeff);
	tmp = sqrt(pow(coeff[1], 2) - 4 * coeff[0] * coeff[2]);
	if (isnan(tmp))
		return (0);
	k = ((-coeff[1] - tmp) / (2 * coeff[0]));
	if (k < MIN_DIST || max_dist < k || check_height(self, ray, k))
	{
		k = ((-coeff[1] + tmp) / (2 * coeff[0]));
		if (k < MIN_DIST || max_dist < k || check_height(self, ray, k))
			return (0);
	}
	*dist = k;
	return (1);
}
