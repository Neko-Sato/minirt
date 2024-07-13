/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   methods_0.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 19:07:39 by hshimizu          #+#    #+#             */
/*   Updated: 2024/07/13 15:45:02 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects/abstract_figure.h"
#include "objects/triangle.h"
#include "utils/vec3d.h"
#include "constants.h"
#include <math.h>

void	triangle_calculate_aabb(t_triangle *self)
{
	t_abstract_figure *const	figure = (t_abstract_figure *)self;

	figure->aabb.min = (t_vec3d){{
		self->a._[0] + fmin(0, fmin(self->ab._[0], self->ac._[0])),
		self->a._[1] + fmin(0, fmin(self->ab._[1], self->ac._[1])),
		self->a._[2] + fmin(0, fmin(self->ab._[2], self->ac._[2])),
	}};
	figure->aabb.max = (t_vec3d){{
		self->a._[0] + fmax(0, fmax(self->ab._[0], self->ac._[0])),
		self->a._[1] + fmax(0, fmax(self->ab._[1], self->ac._[1])),
		self->a._[2] + fmax(0, fmax(self->ab._[2], self->ac._[2])),
	}};
}

int	triangle_intersect(t_triangle *self, const t_ray *ray, float max_dist,
		float *dist)
{
	t_vec3d	s;
	t_vec3d	alpha;
	t_vec3d	beta;
	float	uvt[3];
	float	det;

	if (!aabb_contains(&((t_abstract_figure *)self)->aabb, ray, max_dist))
		return (0);
	alpha = vec3d_cross(ray->o, self->ac);
	det = vec3d_dot(self->ab, alpha);
	if (!det)
		return (0);
	s = vec3d_sub(ray->c, self->a);
	uvt[0] = vec3d_dot(alpha, s) / det;
	if (uvt[0] < 0 || 1 < uvt[0])
		return (0);
	beta = vec3d_cross(s, self->ab);
	uvt[1] = vec3d_dot(ray->o, beta) / det;
	if (uvt[1] < 0 || 1 < uvt[0] + uvt[1])
		return (0);
	uvt[2] = vec3d_dot(self->ac, beta) / det;
	if (uvt[2] < MIN_DIST || max_dist < uvt[2])
		return (0);
	*dist = uvt[2];
	return (1);
}

t_ray	triangle_get_normal(t_triangle *self, float dist, const t_ray *ray)
{
	const t_vec3d	point = vec3d_add(ray->c, vec3d_mul(dist, ray->o));
	t_vec3d			normal;

	if (vec3d_dot(self->normal, vec3d_sub(ray->c, point)) < 0)
		normal = vec3d_mul(-1, self->normal);
	else
		normal = self->normal;
	return ((t_ray){normal, point});
}
