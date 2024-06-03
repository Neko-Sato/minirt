/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 22:50:33 by hshimizu          #+#    #+#             */
/*   Updated: 2024/06/04 02:38:42 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects/camera.h"
#include "rt_errno.h"
#include <stdlib.h>

const t_class_camera	g_class_camera = {
	.init = __camera_init,
	.del = __camera_del,
};

int	__camera_init(t_camera *self)
{
	*self = (t_camera){};
	self->__class = &g_class_camera;
	self->coordinates = (t_vec3d){{0, 0, 0}};
	self->orientation = (t_vec3d){{0, 0, 1}};
	self->fov = 60;
	return (NO_ERROR);
}

void	__camera_del(t_camera *self)
{
	(void)self;
}
