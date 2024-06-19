/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere_0.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 00:58:48 by hshimizu          #+#    #+#             */
/*   Updated: 2024/06/19 16:14:10 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects/sphere.h"
#include "objects/figure.h"
#include "rt_errno.h"
#include <stdlib.h>

int	sphere_init(t_sphere *self)
{
	static const t_figure_vtable	vtable = {
		.del = (void *)sphere_del,
	};
	int								ret;

	*self = (t_sphere){};
	ret = figure_init((t_figure *)self);
	if (ret)
		return (ret);
	((t_figure *)self)->_ = &vtable;
	self->diameter = 1.;
	return (SUCCESS);
}

void	sphere_del(t_sphere *self)
{
	figure_del((t_figure *)self);
}

/*
	Nothing else is this easy.
*/
void	sphere_update_aabb(t_sphere *self)
{
	t_figure *const	figure = (t_figure *)self;
	const float		r = self->diameter / 2.;

	figure->aabb[0] = (t_vec3d){{
		self->coordinates._[0] - r,
		self->coordinates._[1] - r,
		self->coordinates._[2] - r}};
	figure->aabb[1] = (t_vec3d){{
		self->coordinates._[0] + r,
		self->coordinates._[1] + r,
		self->coordinates._[2] + r}};
}
