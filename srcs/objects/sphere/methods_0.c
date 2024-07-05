/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   methods_0.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 19:07:39 by hshimizu          #+#    #+#             */
/*   Updated: 2024/07/05 21:15:40 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects/figure.h"
#include "objects/sphere.h"
#include <math.h>
#include <stdlib.h>

void	sphere_set_aabb(t_sphere *self)
{
	t_figure *const	figure = (t_figure *)self;

	figure->aabb[0] = (t_vec3d){{
		self->coord._[0] - self->radius,
		self->coord._[1] - self->radius,
		self->coord._[2] - self->radius
	}};
	figure->aabb[1] = (t_vec3d){{
		self->coord._[0] + self->radius,
		self->coord._[1] + self->radius,
		self->coord._[2] + self->radius
	}};
}

int	sphere_intersect(t_sphere *self, const t_ray *r, float max_dist, float *t)
{
	int		i;
	float	k;
	float	coeff[3];
	float	tmp;

	if (!figure_intersect((t_figure *)self, r, max_dist, &(float){0}))
		return (0);
	ft_memcpy(coeff, (float [3]){0, 0, -pow(self->radius, 2)}, sizeof(coeff));
	i = 0;
	while (i < 3)
	{
		coeff[0] += pow(r->o._[i], 2);
		coeff[1] += 2 * r->o._[i] * (r->c._[i] - self->coord._[i]);
		coeff[2] += pow(r->c._[i] - self->coord._[i], 2);
		i++;
	}
	tmp = pow(coeff[1], 2) - 4 * coeff[0] * coeff[2];
	if (tmp < 0)
		return (0);
	tmp = sqrt(tmp);
	k = ((-coeff[1] - tmp) / (2 * coeff[0]));
	if (k < 0 || max_dist < k)
		return (0);
	*t = k;
	return (1);
}

t_ray	sphere_get_normal(t_sphere *self, float dist, const t_ray *r)
{
	const t_vec3d	point = vec3d_add(r->c, vec3d_mul(dist, r->o));
	t_vec3d			normal;

	normal = vec3d_norm(vec3d_sub(point, self->coord));
	if (vec3d_dot(normal, vec3d_sub(r->c, point)) < 0)
		normal = vec3d_mul(-1, normal);
	return ((t_ray){normal, point});
}
