/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_0.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 22:50:33 by hshimizu          #+#    #+#             */
/*   Updated: 2024/06/12 12:36:25 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects/camera.h"
#include "rt_errno.h"

int	camera_init(t_camera *self)
{
	*self = (t_camera){};
	self->coordinates = (t_vec3d){{0, 0, 0}};
	self->orientation = (t_vec3d){{0, 0, 1}};
	self->fov = 60;
	self->width = DEFAULT_WIDTH;
	self->height = DEFAULT_HEIGHT;
	return (NO_ERROR);
}

void	camera_del(t_camera *self)
{
	(void)self;
}