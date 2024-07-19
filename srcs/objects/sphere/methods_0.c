/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   methods_0.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 19:07:39 by hshimizu          #+#    #+#             */
/*   Updated: 2024/07/20 01:00:15 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects/abstract_figure.h"
#include "objects/sphere.h"
#include "utils/aabb.h"
#include "utils/ray.h"
#include "constants.h"
#include <math.h>
#include <stdlib.h>
#include <libft.h>

void	sphere_calculate_aabb(t_sphere *self)
{
	t_abstract_figure *const	figure = (t_abstract_figure *)self;

	figure->aabb.min = (t_vec3d){{
		self->coord._[0] - self->radius,
		self->coord._[1] - self->radius,
		self->coord._[2] - self->radius
	}};
	figure->aabb.max = (t_vec3d){{
		self->coord._[0] + self->radius,
		self->coord._[1] + self->radius,
		self->coord._[2] + self->radius
	}};
}

static void	make_coeff(t_sphere *self, const t_ray *r, float coeff[3])
{
	int	i;

	coeff[0] = 0;
	coeff[1] = 0;
	coeff[2] = -pow(self->radius, 2);
	i = 0;
	while (i < 3)
	{
		coeff[0] += pow(r->o._[i], 2);
		coeff[1] += 2 * r->o._[i] * (r->c._[i] - self->coord._[i]);
		coeff[2] += pow(r->c._[i] - self->coord._[i], 2);
		i++;
	}
}

int	sphere_intersect(t_sphere *self, const t_ray *ray, float max_dist,
	float *dist)
{
	float	coeff[3];
	float	tmp;
	float	k;

	if (!aabb_contains(&((t_abstract_figure *)self)->aabb, ray, max_dist))
		return (0);
	make_coeff(self, ray, coeff);
	tmp = pow(coeff[1], 2) - 4 * coeff[0] * coeff[2];
	if (tmp < 0)
		return (0);
	tmp = sqrt(tmp);
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

t_ray	sphere_get_normal(t_sphere *self, float dist, const t_ray *ray)
{
	const t_vec3d	point = vec3d_add(ray->c, vec3d_mul(dist, ray->o));
	t_vec3d			normal;

	normal = vec3d_norm(vec3d_sub(point, self->coord));
	if (vec3d_dot(normal, vec3d_sub(ray->c, point)) < 0)
		normal = vec3d_mul(-1, normal);
	return ((t_ray){normal, point});
}

void	sphere_get_uv_coord(t_sphere *self, const t_vec3d *point, float uv[2])
{
	const t_vec3d	c2p = vec3d_norm(vec3d_sub(*point, self->coord));

	uv[0] = atan(c2p._[2] / c2p._[0]) / M_PI + 0.5;
	uv[1] = acos(c2p._[1]) / M_PI;
}
