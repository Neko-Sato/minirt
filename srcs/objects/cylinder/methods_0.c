/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   methods_0.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 04:57:05 by hshimizu          #+#    #+#             */
/*   Updated: 2024/07/24 07:27:29 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects/abstract_figure.h"
#include "objects/cylinder.h"
#include "utils/vec3.h"
#include "utils/aabb.h"
#include <math.h>

void	cylinder_calculate_aabb(t_cylinder *self)
{
	t_abstract_figure *const	figure = (void *)self;
	const t_aabb				aabb = {{{-1, -1, -1}}, {{1, 1, 1}}};

	figure->aabb = aabb_transform(&aabb, &figure->rotation, &figure->position);
}

t_vec3	cylinder_get_normal(t_cylinder *self, const t_vec3 *point)
{
	t_abstract_figure *const	figure = (void *)self;
	const t_vec3				local_point = mat3x3_mul_vec3(\
		figure->rotation_inv, vec3_sub(*point, figure->position));

	return (vec3_norm(mat3x3_mul_vec3(mat3x3_transpose(figure->rotation_inv), \
		(t_vec3){{local_point._[0], 0, local_point._[2]}})));
}

void	cylinder_get_uv_coord(t_cylinder *self, const t_vec3 *point,
	float uv[2])
{
	t_abstract_figure *const	figure = (void *)self;
	const t_vec3				c2p = mat3x3_mul_vec3(\
		figure->rotation_inv, vec3_sub(*point, figure->position));

	uv[0] = atan2(c2p._[0], c2p._[2]) / (2 * M_PI) - 0.5;
	uv[1] = c2p._[1] / 2. + 0.5;
}
