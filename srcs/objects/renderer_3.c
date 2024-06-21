/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer_3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 16:17:05 by hshimizu          #+#    #+#             */
/*   Updated: 2024/06/22 01:19:25 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects/minirt.h"
#include "objects/renderer.h"
#include "rt_errno.h"
#include "utils/matrix3x3.h"
#include "utils/vec3d.h"
#include <math.h>

static inline void	move(t_renderer *self)
{
	t_vec3d	movement;

	movement = (t_vec3d){{
		self->action.left - self->action.right,
		self->action.up - self->action.down,
		self->action.backward - self->action.forward,
	}};
	if (!vec3d_abs(movement))
		return ;
	self->camera->coordinates = vec3d_add(self->camera->coordinates,
			matrix3x3_mul_vec3d(self->camera->transform,
				vec3d_mul(MOVE_UNIT, movement)));
	self->iter = 0;
}

static inline void	route(t_renderer *self)
{
	t_matrix3x3	rotation;
	float		roll;
	float		pitch;
	float		yaw;

	roll = self->action.roll_up - self->action.roll_dn;
	pitch = self->action.pitch_up - self->action.pitch_dn;
	yaw = self->action.yaw_up - self->action.yaw_dn;
	if (!roll && !pitch && !yaw)
		return ;
	rotation = matrix3x3_rotation_rollpitchyaw(
			ROTATE_UNIT * roll, ROTATE_UNIT * pitch, ROTATE_UNIT * yaw);
	self->camera->transform = matrix3x3_mul(self->camera->transform, rotation);
	self->iter = 0;
}

static inline void	fov(t_renderer *self)
{
	float	tmp;

	tmp = self->action.broaden - self->action.narrow;
	if (!tmp)
		return ;
	tmp = ft_deg2rad(1. * tmp) + self->camera->fov;
	if (!ALLOW_FOV_UNLIMITED && (tmp < 0 || M_PI < tmp))
		return ;
	self->camera->fov = tmp;
	self->iter = 0;
}

static inline void	action(t_renderer *self)
{
	if (self->action.reset)
	{
		self->action.reset = 0;
		*self->camera = self->save;
		self->iter = 0;
		return ;
	}
	move(self);
	route(self);
	fov(self);
}

int	renderer_loop_hook(t_renderer *self)
{
	if (!self->focus)
		return (SUCCESS);
	action(self);
	if (self->max_iter <= self->iter)
		return (SUCCESS);
	return (renderer_render(self));
}
