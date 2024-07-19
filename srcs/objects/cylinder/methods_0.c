/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   methods_0.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 04:57:05 by hshimizu          #+#    #+#             */
/*   Updated: 2024/07/20 04:35:32 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects/abstract_figure.h"
#include "objects/cylinder.h"
#include "rt_errno.h"
#include "constants.h"
#include "utils/vec3d.h"
#include "utils/ray.h"
#include "utils/matrix3x3.h"
#include "utils/aabb.h"
#include <math.h>

void	cylinder_calculate_aabb(t_cylinder *self)
{
	t_abstract_figure *const	figure = (t_abstract_figure *)self;
	t_vec3d						tmp;
	t_vec3d						axis;

	axis = (t_vec3d){{fabs(self->axis._[0]), fabs(self->axis._[1]),
		fabs(self->axis._[2])}};
	tmp = matrix3x3_mul_vec3d(matrix3x3_transform((t_vec3d){{0, 0, 1}}, axis),
			(t_vec3d){{self->radius, self->radius, 0}});
	tmp = (t_vec3d){{fabs(tmp._[0]), fabs(tmp._[1]), fabs(tmp._[2])}};
	tmp = vec3d_add(vec3d_mul(self->height / 2., axis), tmp);
	figure->aabb.min = vec3d_sub(self->coord, tmp);
	figure->aabb.max = vec3d_add(self->coord, tmp);
}

static void	make_coeff(t_cylinder *self, const t_ray *r, float coeff[3])
{
	const t_vec3d	a = vec3d_cross(self->axis, r->o);
	const t_vec3d	b = vec3d_cross(self->axis, vec3d_sub(r->c, self->coord));

	coeff[0] = pow(vec3d_abs(a), 2);
	coeff[1] = 2 * vec3d_dot(a, b);
	coeff[2] = pow(vec3d_abs(b), 2) - pow(self->radius, 2)
		* pow(vec3d_abs(self->axis), 2);
}

int	cylinder_intersect(t_cylinder *self, const t_ray *ray, float max_dist,
		float *dist)
{
	float	coeff[3];
	float	tmp;
	float	height;
	float	k;

	if (!aabb_contains(&((t_abstract_figure *)self)->aabb, ray, max_dist))
		return (0);
	make_coeff(self, ray, coeff);
	tmp = pow(coeff[1], 2) - 4 * coeff[0] * coeff[2];
	if (tmp < 0)
		return (0);
	tmp = sqrt(tmp);
	k = ((-coeff[1] - tmp) / (2 * coeff[0]));
	height = vec3d_dot(self->axis, vec3d_sub(
				vec3d_add(vec3d_mul(k, ray->o), ray->c), self->coord));
	if (k < MIN_DIST || max_dist < k || self->height / 2. < fabs(height))
	{
		k = ((-coeff[1] + tmp) / (2 * coeff[0]));
		height = vec3d_dot(self->axis, vec3d_sub(
					vec3d_add(vec3d_mul(k, ray->o), ray->c), self->coord));
		if (k < MIN_DIST || max_dist < k || self->height / 2. < fabs(height))
			return (0);
	}
	*dist = k;
	return (1);
}

t_ray	cylinder_get_normal(t_cylinder *self, float dist, const t_ray *r)
{
	const t_vec3d	point = vec3d_add(r->c, vec3d_mul(dist, r->o));
	t_vec3d			coord2point;
	t_vec3d			normal;

	coord2point = vec3d_sub(point, self->coord);
	normal = vec3d_norm(vec3d_sub(coord2point, vec3d_mul(vec3d_dot(coord2point,
						self->axis), self->axis)));
	if (vec3d_dot(normal, vec3d_sub(r->c, point)) < 0)
		normal = vec3d_mul(-1, normal);
	return ((t_ray){normal, point});
}

void	cylinder_get_uv_coord(t_cylinder *self, const t_vec3d *point,
	float uv[2])
{
	(void)self;
	(void)point;
	uv[0] = 0;
	uv[1] = 0;
}
