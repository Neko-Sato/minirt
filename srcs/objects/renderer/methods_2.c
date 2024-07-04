/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   methods_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 16:17:05 by hshimizu          #+#    #+#             */
/*   Updated: 2024/07/05 07:10:04 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects/camera.h"
#include "objects/minirt.h"
#include "objects/renderer.h"
#include "rt_errno.h"
#include "utils/vec3d.h"

static inline void	move(t_renderer *self)
{
	t_vec3d	movement;

	movement = (t_vec3d){{
		MOVE_UNIT * (self->action.left - self->action.right),
		MOVE_UNIT * (self->action.up - self->action.down),
		MOVE_UNIT * (self->action.backward - self->action.forward),
	}};
	if (!vec3d_abs(movement))
		return ;
	camera_move(self->camera, &movement);
	self->iter = -1;
}

static inline void	route(t_renderer *self)
{
	float		roll;
	float		pitch;
	float		yaw;

	roll = ROTATE_UNIT * (self->action.roll_up - self->action.roll_dn);
	pitch = ROTATE_UNIT * (self->action.pitch_up - self->action.pitch_dn);
	yaw = ROTATE_UNIT * (self->action.yaw_up - self->action.yaw_dn);
	if (!roll && !pitch && !yaw)
		return ;
	camera_rotate(self->camera, roll, pitch, yaw);
	self->iter = -1;
}

static inline void	fov(t_renderer *self)
{
	float	tmp;

	tmp = self->action.broaden - self->action.narrow;
	if (!tmp)
		return ;
	if (camera_fov(self->camera, ft_deg2rad(tmp) + self->camera->fov))
		return ;
	self->iter = -1;
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

t_rt_errno	renderer_loop_hook(t_renderer *self)
{
	if (!self->focus)
		return (SUCCESS);
	action(self);
	if (self->iter < 0)
		;
	else if (self->box[0] <= self->iter / self->box[1])
		return (SUCCESS);
	return (renderer_render(self));
}
