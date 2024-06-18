/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   figure_0.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 00:58:30 by hshimizu          #+#    #+#             */
/*   Updated: 2024/06/18 19:08:39 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects/figure.h"
#include "rt_errno.h"
#include <stdlib.h>
#include <math.h>

int	figure_init(t_figure *self)
{
	static const t_figure_vtable	vtable = {
		.del = figure_del,
	};

	*self = (t_figure){};
	self->_ = &vtable;
	self->color = (t_color){.raw = COLOR_RAW_RED};
	self->reflectivity = 0.;
	self->checker = (t_color){.raw = COLOR_RAW_TRANSPARENT};
	self->bump = NULL;
	self->aabb[0] = (t_vec3d){{INFINITY, INFINITY, INFINITY}};
	self->aabb[1] = (t_vec3d){{-INFINITY, -INFINITY, -INFINITY}};
	return (NO_ERROR);
}

void	figure_del(t_figure *self)
{
	free(self->bump);
}
