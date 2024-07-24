/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   methods_0.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 19:07:39 by hshimizu          #+#    #+#             */
/*   Updated: 2024/07/24 11:45:48 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects/abstract_figure.h"
#include "objects/triangle.h"
#include "utils/vec3.h"

void	triangle_calculate_aabb(t_triangle *self)
{
	t_abstract_figure *const	figure = (void *)self;

	figure->aabb = aabb_transform(
			&(t_aabb){{{0, 0, 0}}, {{1, 1, 0}}},
			&figure->rotation,
			&figure->position
			);
}

t_vec3	triangle_get_normal(t_triangle *self, const t_vec3 *point)
{
	t_abstract_figure *const	figure = (void *)self;

	(void)point;
	return (vec3_norm(mat3x3_mul_vec3(mat3x3_transpose(figure->rotation_inv), \
		(t_vec3){{0, 0, 1}})));
}

void	triangle_get_uv_coord(t_triangle *self, const t_vec3 *point,
	float uv[2])
{
	t_abstract_figure *const	figure = (void *)self;
	const t_vec3				local_point = mat3x3_mul_vec3(\
		figure->rotation_inv, vec3_sub(*point, figure->position));

	uv[0] = local_point._[0] / (1 - local_point._[1]);
	uv[1] = local_point._[1];
}
