/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   methods_1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 17:50:04 by hshimizu          #+#    #+#             */
/*   Updated: 2024/07/24 08:01:05 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects/abstract_figure.h"
#include "objects/plane.h"
#include "utils/vec3.h"
#include "utils/ray.h"
#include "constants.h"

static inline void	make_coeff(t_plane *self, const t_ray *ray, float coeff[2])
{
	t_abstract_figure *const	figure = (void *)self;
	const t_ray					local_ray = {
		mat3x3_mul_vec3(figure->rotation_inv, ray->o),
		mat3x3_mul_vec3(figure->rotation_inv,
			vec3_sub(ray->c, figure->position))
	};

	coeff[0] = local_ray.o._[1];
	coeff[1] = local_ray.c._[1];
}

int	plane_intersect(t_plane *self, const t_ray *ray, float max_dist,
		float *dist)
{
	float						coeff[2];
	float						k;

	make_coeff(self, ray, coeff);
	k = -coeff[1] / coeff[0];
	if (k < MIN_DIST || max_dist < k)
		return (0);
	*dist = k;
	return (1);
}
