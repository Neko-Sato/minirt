/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   methods_0.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 04:37:36 by hshimizu          #+#    #+#             */
/*   Updated: 2024/07/20 20:47:38 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects/camera.h"
#include "utils/matrix3x3.h"
#include "utils/vec3d.h"
#include <math.h>

void	camera_move(t_camera *self, const t_vec3d *direction)
{
	self->coord = vec3d_add(
			self->coord,
			matrix3x3_mul_vec3d(self->transform, *direction));
}

void	camera_rotate(t_camera *self, float roll, float pitch, float yaw)
{
	self->transform = matrix3x3_mul(self->transform,
			matrix3x3_rotation_rollpitchyaw(roll, pitch, yaw));
}

void	camera_set_fov(t_camera *self, float fov)
{
	self->fov = fov;
}
