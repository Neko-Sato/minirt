/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   methods_0.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 04:37:36 by hshimizu          #+#    #+#             */
/*   Updated: 2024/07/28 15:29:48 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects/camera.h"
#include "utils/mat3x3.h"
#include "utils/vec3.h"
#include <math.h>

void	camera_move(t_camera *self, const t_vec3 *direction)
{
	self->coord = vec3_add(
			self->coord,
			mat3x3_mul_vec3(self->transform, *direction));
}

void	camera_rotate(t_camera *self, float roll, float pitch, float yaw)
{
	self->transform = mat3x3_mul(self->transform,
			mat3x3_rotation_rollpitchyaw(roll, pitch, yaw));
}

void	camera_set_fov(t_camera *self, float fov)
{
	self->fov = fov;
}

void	camera_put_info(t_camera *self)
{
	(void)self;
}
