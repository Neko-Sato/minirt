/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_0.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 00:58:41 by hshimizu          #+#    #+#             */
/*   Updated: 2024/06/19 18:05:08 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects/cylinder.h"
#include "objects/figure.h"
#include "rt_errno.h"
#include <math.h>

int	cylinder_init(t_cylinder *self)
{
	static const t_figure_vtable	vtable = {
		.del = (void *)cylinder_del,
	};
	int								ret;

	*self = (t_cylinder){};
	ret = figure_init((t_figure *)self);
	if (ret)
		return (ret);
	((t_figure *)self)->_ = &vtable;
	self->axis = (t_vec3d){{0, 1, 0}};
	self->diameter = 5.;
	self->height = 10.;
	return (SUCCESS);
}

void	cylinder_del(t_cylinder *self)
{
	figure_del((t_figure *)self);
}

/*
	It should be rectangular.
	Let's solve this by giving it a suitable upward vector instead.
	hmmm, I feel like that's a good idea.
	It's not going to make a difference after all.

	I don't feel like it's very good...
*/
void	cylinder_update_aabb(t_cylinder *self)
{
	t_figure *const	figure = (t_figure *)self;
	const t_vec3d	u = vec3d_norm(self->axis);
	const t_vec3d	r = vec3d_norm(vec3d_cross(
				(t_vec3d []){{{0, 1, 0}}, {{1, 0, 0}}}[!u._[0] && !u._[2]], u));
	const t_vec3d	u1 = vec3d_mul(self->height / 2., u);
	const t_vec3d	r1 = vec3d_mul(self->diameter / 2., r);

	figure->aabb[0] = (t_vec3d){{
		self->coordinates._[0] - fabs(r1._[0]) - fabs(u1._[0]),
		self->coordinates._[1] - fabs(r1._[1]) - fabs(u1._[1]),
		self->coordinates._[2] - fabs(r1._[2]) - fabs(u1._[2])}};
	figure->aabb[1] = (t_vec3d){{
		self->coordinates._[0] + fabs(r1._[0]) + fabs(u1._[0]),
		self->coordinates._[1] + fabs(r1._[1]) + fabs(u1._[1]),
		self->coordinates._[2] + fabs(r1._[2]) + fabs(u1._[2])}};
}
