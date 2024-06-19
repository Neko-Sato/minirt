/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   square_0.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 22:50:33 by hshimizu          #+#    #+#             */
/*   Updated: 2024/06/19 16:14:10 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects/figure.h"
#include "objects/square.h"
#include "rt_errno.h"
#include <math.h>
#include <stdlib.h>

int	square_init(t_square *self)
{
	static const t_figure_vtable	vtable = {
		.del = (void *)square_del,
	};
	int								ret;

	*self = (t_square){};
	ret = figure_init((t_figure *)self);
	if (ret)
		return (-1);
	((t_figure *)self)->_ = &vtable;
	self->orientation = (t_vec3d){{0, 1, 1}};
	self->size = 10.;
	return (SUCCESS);
}

void	square_del(t_square *self)
{
	figure_del((t_figure *)self);
}

/*
	AABB may not be necessary
	if it does not have volume, like a triangle.
*/
void	square_update_aabb(t_square *self)
{
	(void)self;
}
