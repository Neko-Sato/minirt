/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   methods_0.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 19:07:39 by hshimizu          #+#    #+#             */
/*   Updated: 2024/07/24 07:42:01 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects/abstract_figure.h"
#include "objects/sphere.h"
#include "utils/aabb.h"
#include <math.h>

void	sphere_calculate_aabb(t_sphere *self)
{
	t_abstract_figure *const	figure = (void *)self;

	figure->aabb = aabb_transform(
			&(t_aabb){{{-1, -1, -1}}, {{1, 1, 1}}},
			&figure->rotation,
			&figure->position
			);
}

t_vec3	sphere_get_normal(t_sphere *self, const t_vec3 *point)
{
	t_abstract_figure *const	figure = (void *)self;
	const t_vec3				local_point = mat3x3_mul_vec3(\
		figure->rotation_inv, vec3_sub(*point, figure->position));

	return (vec3_norm(mat3x3_mul_vec3(mat3x3_transpose(figure->rotation_inv), \
		local_point)));
}

void	sphere_get_uv_coord(t_sphere *self, const t_vec3 *point, float uv[2])
{
	t_abstract_figure *const	figure = (void *)self;
	const t_vec3				c2p = mat3x3_mul_vec3(\
		figure->rotation_inv, vec3_sub(*point, figure->position));

	uv[0] = atan2(c2p._[0], c2p._[2]) / (2 * M_PI) - 0.5;
	uv[1] = 1 - acos(c2p._[1] / vec3_abs(c2p)) / M_PI;
}
