/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   triangle_0.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 22:50:33 by hshimizu          #+#    #+#             */
/*   Updated: 2024/06/19 16:14:10 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects/figure.h"
#include "objects/triangle.h"
#include "rt_errno.h"
#include <math.h>
#include <stdlib.h>

int	triangle_init(t_triangle *self)
{
	static const t_figure_vtable	vtable = {
		.del = (void *)triangle_del,
	};
	int								ret;

	*self = (t_triangle){};
	ret = figure_init((t_figure *)self);
	if (ret)
		return (-1);
	((t_figure *)self)->_ = &vtable;
	self->first = (t_vec3d){{0, 1, 0}};
	self->second = (t_vec3d){{-1, 0, 0}};
	self->third = (t_vec3d){{1, 0, 0}};
	return (SUCCESS);
}

void	triangle_del(t_triangle *self)
{
	figure_del((t_figure *)self);
}

/*
	For triangles,
	there must have been a better algorithm using the outer product.
*/
void	triangle_update_aabb(t_triangle *self)
{
	(void)self;
}
