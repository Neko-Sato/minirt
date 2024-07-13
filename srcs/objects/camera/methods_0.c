/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   methods_0.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 04:37:36 by hshimizu          #+#    #+#             */
/*   Updated: 2024/07/14 05:12:40 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects/camera.h"
#include "utils/matrix3x3.h"
#include "utils/vec3d.h"
#include "constants.h"
#include <math.h>

int	camera_move(t_camera *self, const t_vec3d *direction)
{
	self->coord = vec3d_add(
			self->coord,
			matrix3x3_mul_vec3d(self->transform, *direction));
	return (0);
}

int	camera_rotate(t_camera *self, float roll, float pitch, float yaw)
{
	self->transform = matrix3x3_mul(self->transform,
			matrix3x3_rotation_rollpitchyaw(roll, pitch, yaw));
	return (0);
}

int	camera_set_fov(t_camera *self, float fov)
{
	if (!ALLOW_FOV_UNLIMITED && (fov < 0 || M_PI < fov))
		return (1);
	self->fov = fov;
	return (0);
}
