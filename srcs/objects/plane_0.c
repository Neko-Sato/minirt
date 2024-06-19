/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane_0.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 22:50:33 by hshimizu          #+#    #+#             */
/*   Updated: 2024/06/18 20:05:38 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects/figure.h"
#include "objects/plane.h"
#include "utils/vec3d.h"
#include "rt_errno.h"
#include <math.h>
#include <stdlib.h>

int	plane_init(t_plane *self)
{
	static const t_figure_vtable	vtable = {
		.del = (void *)plane_del,
	};
	int								ret;

	*self = (t_plane){};
	ret = figure_init((t_figure *)self);
	if (ret)
		return (-1);
	((t_figure *)self)->_ = &vtable;
	self->orientation = (t_vec3d){{0, 1, 1}};
	return (SUCCESS);
}

void	plane_del(t_plane *self)
{
	figure_del((t_figure *)self);
}

/*
	Since the size is infinite, they basically collide.
	If parallel to the basis, it should be an exception.
*/
void	plane_update_aabb(t_plane *self)
{
	t_figure *const	figure = (t_figure *)self;
	const t_vec3d	f = self->orientation;

	figure->aabb[0] = (t_vec3d){{-INFINITY, -INFINITY, -INFINITY}};
	figure->aabb[1] = (t_vec3d){{INFINITY, INFINITY, INFINITY}};
	if (!f._[1] && !f._[2])
	{
		figure->aabb[0]._[0] = self->coordinates._[0];
		figure->aabb[1]._[0] = self->coordinates._[0];
	}
	else if (!f._[0] && !f._[2])
	{
		figure->aabb[0]._[1] = self->coordinates._[1];
		figure->aabb[1]._[1] = self->coordinates._[1];
	}
	else if (!f._[0] && !f._[1])
	{
		figure->aabb[0]._[2] = self->coordinates._[2];
		figure->aabb[1]._[2] = self->coordinates._[2];
	}
}
