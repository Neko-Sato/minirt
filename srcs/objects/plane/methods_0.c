/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   methods_0.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 17:50:04 by hshimizu          #+#    #+#             */
/*   Updated: 2024/07/05 22:14:45 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects/figure.h"
#include "objects/plane.h"
#include <math.h>

void	plane_set_aabb(t_plane *self)
{
	t_figure *const	figure = (t_figure *)self;
	const t_vec3d	f = self->orient;

	figure->aabb[0] = (t_vec3d){{-INFINITY, -INFINITY, -INFINITY}};
	figure->aabb[1] = (t_vec3d){{INFINITY, INFINITY, INFINITY}};
	if (!f._[0])
	{
		if (!f._[1])
		{
			figure->aabb[0]._[2] = self->coord._[2];
			figure->aabb[1]._[2] = self->coord._[2];
		}
		else if (!f._[2])
		{
			figure->aabb[0]._[1] = self->coord._[1];
			figure->aabb[1]._[1] = self->coord._[1];
		}
	}
	else if (!f._[1] && !f._[2])
	{
		figure->aabb[0]._[0] = self->coord._[0];
		figure->aabb[1]._[0] = self->coord._[0];
	}
}

int	plane_intersect(t_plane *self, const t_ray *r, float max_dist, float *t)
{
	int		i;
	float	a;
	float	b;
	float	k;

	if (!figure_intersect((t_figure *)self, r, max_dist, &(float){0}))
		return (0);
	a = 0;
	b = 0;
	i = 0;
	while (i < 3)
	{
		a += self->orient._[i] * r->o._[i];
		b += self->orient._[i] * (r->c._[i] - self->coord._[i]);
		i++;
	}
	k = -b / a;
	if (k < 0 || max_dist < k)
		return (0);
	*t = k;
	return (1);
}

t_ray	plane_get_normal(t_plane *self, float dist, const t_ray *r)
{
	const t_vec3d	point = vec3d_add(r->c, vec3d_mul(dist, r->o));
	t_vec3d			normal;

	if (vec3d_dot(self->orient, vec3d_sub(r->c, point)) < 0)
		normal = vec3d_mul(-1, self->orient);
	else
		normal = self->orient;
	return ((t_ray){normal, point});
}
