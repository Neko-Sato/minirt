/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   figure_0.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 00:58:30 by hshimizu          #+#    #+#             */
/*   Updated: 2024/06/12 12:36:28 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects/figure.h"
#include "rt_errno.h"
#include <stdlib.h>

int	figure_init(t_figure *self)
{
	static const t_figure_vtable	vtable = {
		.del = figure_del,
	};

	*self = (t_figure){};
	self->_ = &vtable;
	self->coordinates = (t_vec3d){{0, 0, 10}};
	self->color = (t_color){.raw = COLOR_RAW_RED};
	self->reflectivity = 0.;
	self->checker = (t_color){.raw = COLOR_RAW_TRANSPARENT};
	self->bump = NULL;
	return (NO_ERROR);
}

void	figure_del(t_figure *self)
{
	free(self->bump);
}
