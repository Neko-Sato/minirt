/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 22:50:33 by hshimizu          #+#    #+#             */
/*   Updated: 2024/06/04 02:40:54 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects/plane.h"
#include "rt_errno.h"
#include <stdlib.h>

const t_class_plane	g_class_plane = {
	.init = __plane_init,
	.del = __plane_del,
};

int	__plane_init(t_plane *self)
{
	int	ret;

	*self = (t_plane){};
	self->__class = &g_class_plane;
	ret = __figure_init(&self->__parent);
	if (ret)
		return (-1);
	self->normal = (t_vec3d){{0, 1, 1}};
	return (NO_ERROR);
}

void	__plane_del(t_plane *self)
{
	self->__parent.__class->del(&self->__parent);
}
