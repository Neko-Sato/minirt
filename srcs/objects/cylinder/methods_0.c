/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   methods_0.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 04:57:05 by hshimizu          #+#    #+#             */
/*   Updated: 2024/07/02 00:47:03 by hshimizu         ###   ########.fr       */
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

	figure->aabb[0] = (t_vec3d){{
		self->r_coord._[0] - self->radius,
		self->r_coord._[1] - self->height / 2.,
		self->r_coord._[2] - self->radius
	}};
	figure->aabb[1] = (t_vec3d){{
		self->r_coord._[0] + self->radius,
		self->r_coord._[1] + self->height / 2.,
		self->r_coord._[2] + self->radius
	}};
}

static int	solve(t_cylinder *self, const t_ray *r, float k[2])
{
	float	coeff[3];
	float	tmp;

	coeff[0] = pow(r->o._[0], 2) + pow(r->o._[2], 2);
	coeff[1] = 2 * (r->o._[0] * (r->c._[0] - self->r_coord._[0])
			+ r->o._[2] * (r->c._[2] - self->r_coord._[2]));
	coeff[2] = pow(r->c._[0] - self->r_coord._[0], 2) + pow(r->c._[2]
			- self->r_coord._[2], 2) - pow(self->radius, 2);
	tmp = pow(coeff[1], 2) - 4 * coeff[0] * coeff[2];
	if (tmp < 0)
		return (1);
	tmp = sqrt(tmp);
	k[0] = ((-coeff[1] - tmp) / (2 * coeff[0]));
	k[1] = ((-coeff[1] + tmp) / (2 * coeff[0]));
	return (0);
}

int	cylinder_intersect(t_cylinder *self, const t_ray *r, float max_dist,
		float *t)
{
	t_ray	r_r;
	float	k[2];
	int		i;

	r_r = (t_ray){matrix3x3_mul_vec3d(self->rotation, r->o),
		matrix3x3_mul_vec3d(self->rotation, r->c)};
	if (!figure_intersect((t_figure *)self, &r_r, max_dist, &(float){0}))
		return (0);
	if (solve(self, &r_r, k))
		return (0);
	i = 0;
	while (i < 2)
	{
		if (0 < k[i] && k[i] < max_dist
			&& fabs(vec3d_dot(
					(t_vec3d){{0, 1, 0}},
				vec3d_sub(vec3d_add(vec3d_mul(k[i], r_r.o), r_r.c),
					self->r_coord))) < self->height / 2.)
			break ;
		i++;
	}
	if (i < 2)
		*t = k[i];
	return (i < 2);
}
