/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane_0.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 22:50:33 by hshimizu          #+#    #+#             */
/*   Updated: 2024/06/12 12:36:38 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects/plane.h"
#include "objects/figure.h"
#include "rt_errno.h"
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
	self->normal = (t_vec3d){{0, 1, 1}};
	return (NO_ERROR);
}

void	plane_del(t_plane *self)
{
	figure_del((t_figure *)self);
}
