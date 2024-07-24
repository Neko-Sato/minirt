/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   methods_0.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 17:50:04 by hshimizu          #+#    #+#             */
/*   Updated: 2024/07/24 07:26:49 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects/abstract_figure.h"
#include "objects/plane.h"
#include "utils/aabb.h"
#include "utils/vec3.h"
#include <math.h>

void	plane_calculate_aabb(t_plane *self)
{
	t_abstract_figure *const	figure = (void *)self;
	const t_aabb				aabb = \
		{{{-INFINITY, 0, -INFINITY}}, {{INFINITY, 0, INFINITY}}};

	figure->aabb = aabb_transform(&aabb, &figure->rotation, &figure->position);
}

t_vec3	plane_get_normal(t_plane *self, const t_vec3 *point)
{
	t_abstract_figure *const	figure = (void *)self;

	(void)point;
	return (vec3_norm(mat3x3_mul_vec3(mat3x3_transpose(figure->rotation_inv), \
		(t_vec3){{0, 1, 0}})));
}

void	plane_get_uv_coord(t_plane *self, const t_vec3 *point, float uv[2])
{
	t_abstract_figure *const	figure = (void *)self;
	const t_vec3				local_point = mat3x3_mul_vec3(\
		figure->rotation_inv, *point);

	uv[0] = local_point._[0];
	uv[1] = 1 - local_point._[2];
}
