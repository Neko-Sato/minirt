/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   figure.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 00:58:30 by hshimizu          #+#    #+#             */
/*   Updated: 2024/06/05 00:10:35 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects/cylinder.h"
#include "objects/figure.h"
#include "objects/plane.h"
#include "objects/sphere.h"
#include "rt_errno.h"
#include <stdlib.h>

int	figure_init(t_figure *self)
{
	*self = (t_figure){};
	self->__type = f_none;
	self->coordinates = (t_vec3d){{0, 0, 10}};
	self->color = (t_color){.raw = COLOR_RAW_RED};
	self->reflectivity = 0.;
	self->checker = (t_color){.raw = COLOR_RAW_TRANSPARENT};
	self->bump = NULL;
	return (NO_ERROR);
}

void	figure_del(t_figure *self)
{
	static void (*const	del[])(t_figure *) = {
		__figure_del,
		(t_figure_del)sphere_del,
		(t_figure_del)plane_del,
		(t_figure_del)cylinder_del,
	};

	del[self->__type](self);
}

void	__figure_del(t_figure *self)
{
	free(self->bump);
}
