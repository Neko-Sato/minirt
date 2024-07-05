/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   methods_0.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 04:57:05 by hshimizu          #+#    #+#             */
/*   Updated: 2024/07/05 21:16:26 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects/cylinder.h"
#include "objects/figure.h"
#include "rt_errno.h"
#include "utils/matrix3x3.h"
#include <math.h>

void	cylinder_set_aabb(t_cylinder *self)
{
	t_figure *const	figure = (t_figure *)self;
	t_vec3d			tmp;
	t_vec3d			axis;

	axis = (t_vec3d){{fabs(self->axis._[0]), fabs(self->axis._[1]),
		fabs(self->axis._[2])}};
	tmp = matrix3x3_mul_vec3d(matrix3x3_transform((t_vec3d){{0, 1, 0}}, axis),
			(t_vec3d){{self->radius, 0, self->radius}});
	tmp = (t_vec3d){{fabs(tmp._[0]), fabs(tmp._[1]), fabs(tmp._[2])}};
	tmp = vec3d_add(vec3d_mul(self->height / 2., axis), tmp);
	figure->aabb[0] = vec3d_sub(self->coord, tmp);
	figure->aabb[1] = vec3d_add(self->coord, tmp);
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

int	cylinder_intersect(t_cylinder *self, const t_ray *r, float max_dist,
		float *t)
{
	float	coeff[3];
	float	tmp;
	float	dist;
	float	k;

	if (!figure_intersect((t_figure *)self, r, max_dist, &(float){0}))
		return (0);
	make_coeff(self, r, coeff);
	tmp = pow(coeff[1], 2) - 4 * coeff[0] * coeff[2];
	if (tmp < 0)
		return (0);
	tmp = sqrt(tmp);
	k = ((-coeff[1] - tmp) / (2 * coeff[0]));
	dist = vec3d_dot(self->axis, vec3d_sub(vec3d_add(vec3d_mul(k, r->o), r->c),
				self->coord));
	if (!(0 < k && k < max_dist && fabs(dist) < self->height / 2.))
	{
		k = ((-coeff[1] + tmp) / (2 * coeff[0]));
		dist = vec3d_dot(self->axis, vec3d_sub(vec3d_add(vec3d_mul(k, r->o),
						r->c), self->coord));
		if (!(0 < k && k < max_dist && fabs(dist) < self->height / 2.))
			return (0);
	}
	*t = k;
	return (1);
}

t_ray	cylinder_get_normal(t_cylinder *self, float dist, const t_ray *r)
{
	const t_vec3d	point = vec3d_add(r->c, vec3d_mul(dist, r->o));
	t_vec3d			coord2point;
	t_vec3d			normal;

	coord2point = vec3d_sub(point, self->coord);
	normal = vec3d_sub(coord2point, vec3d_add(self->coord,
				vec3d_mul(vec3d_dot(coord2point, self->axis), self->axis)));
	if (vec3d_dot(normal, vec3d_sub(r->c, point)) < 0)
		normal = vec3d_mul(-1, normal);
	return ((t_ray){normal, point});
}
