/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   figure.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 00:58:30 by hshimizu          #+#    #+#             */
/*   Updated: 2024/06/04 02:55:06 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects/figure.h"
#include "rt_errno.h"
#include <stdlib.h>

const t_class_figure	g_class_figure = {
	.init = __figure_init,
	.del = __figure_del,
};

int	__figure_init(t_figure *self)
{
	*self = (t_figure){};
	self->__class = &g_class_figure;
	self->coordinates = (t_vec3d){{0, 0, 10}};
	self->color = (t_color){.raw = COLOR_RAW_RED};
	self->reflectivity = 0.;
	self->checker = (t_color){.raw = COLOR_RAW_TRANSPARENT};
	self->bump = NULL;
	return (NO_ERROR);
}

void	__figure_del(t_figure *self)
{
	free(self->bump);
	(void)self;
}
