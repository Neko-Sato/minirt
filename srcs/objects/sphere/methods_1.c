/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   methods_1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 19:07:39 by hshimizu          #+#    #+#             */
/*   Updated: 2024/07/24 05:42:02 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects/abstract_figure.h"
#include "objects/sphere.h"
#include "utils/aabb.h"
#include "utils/ray.h"
#include "constants.h"
#include <math.h>

static inline void	make_coeff(t_sphere *self, const t_ray *ray, float coeff[3])
{
	t_abstract_figure *const	figure = (void *)self;
	const t_ray					local_ray = {
		mat3x3_mul_vec3(figure->rotation_inv, ray->o),
		mat3x3_mul_vec3(figure->rotation_inv,
			vec3_sub(ray->c, figure->position))
	};
	int							i;

	coeff[0] = 0;
	coeff[1] = 0;
	coeff[2] = -1;
	i = 0;
	while (i < 3)
	{
		coeff[0] += pow(local_ray.o._[i], 2);
		coeff[1] += 2 * local_ray.o._[i] * local_ray.c._[i];
		coeff[2] += pow(local_ray.c._[i], 2);
		i++;
	}
}

int	sphere_intersect(t_sphere *self, const t_ray *ray, float max_dist,
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
	if (k < MIN_DIST || max_dist < k)
	{
		k = ((-coeff[1] + tmp) / (2 * coeff[0]));
		if (k < MIN_DIST || max_dist < k)
			return (0);
	}
	*dist = k;
	return (1);
}
