/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   methods_0.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 17:50:04 by hshimizu          #+#    #+#             */
/*   Updated: 2024/07/13 15:44:07 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects/abstract_figure.h"
#include "objects/plane.h"
#include "utils/aabb.h"
#include "utils/vec3d.h"
#include "utils/ray.h"
#include "constants.h"
#include <math.h>

void	plane_calculate_aabb(t_plane *self)
{
	t_abstract_figure *const	figure = (t_abstract_figure *)self;
	const t_vec3d				f = self->orient;

	figure->aabb.min = (t_vec3d){{-INFINITY, -INFINITY, -INFINITY}};
	figure->aabb.max = (t_vec3d){{INFINITY, INFINITY, INFINITY}};
	if (!f._[0])
	{
		if (!f._[1])
		{
			figure->aabb.min._[2] = self->coord._[2];
			figure->aabb.max._[2] = self->coord._[2];
		}
		else if (!f._[2])
		{
			figure->aabb.min._[1] = self->coord._[1];
			figure->aabb.max._[1] = self->coord._[1];
		}
	}
	else if (!f._[1] && !f._[2])
	{
		figure->aabb.min._[0] = self->coord._[0];
		figure->aabb.max._[0] = self->coord._[0];
	}
}

int	plane_intersect(t_plane *self, const t_ray *ray, float max_dist,
		float *dist)
{
	int		i;
	float	coeff[2];
	float	k;

	coeff[0] = 0;
	coeff[1] = 0;
	i = 0;
	while (i < 3)
	{
		coeff[0] += self->orient._[i] * ray->o._[i];
		coeff[1] += self->orient._[i] * (ray->c._[i] - self->coord._[i]);
		i++;
	}
	k = -coeff[1] / coeff[0];
	if (k < MIN_DIST || max_dist < k)
		return (0);
	*dist = k;
	return (1);
}

t_ray	plane_get_normal(t_plane *self, float dist, const t_ray *ray)
{
	const t_vec3d	point = vec3d_add(ray->c, vec3d_mul(dist, ray->o));
	t_vec3d			normal;

	if (vec3d_dot(self->orient, vec3d_sub(ray->c, point)) < 0)
		normal = vec3d_mul(-1, self->orient);
	else
		normal = self->orient;
	return ((t_ray){normal, point});
}
