/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   methods_3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 16:17:05 by hshimizu          #+#    #+#             */
/*   Updated: 2024/07/20 20:48:33 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects/camera.h"
#include "objects/minirt.h"
#include "objects/renderer.h"
#include "constants.h"
#include "rt_errno.h"
#include "utils/vec3d.h"
#include <mlx.h>

static inline void	move(t_renderer *self)
{
	const t_vec3d	movement = vec3d_mul(MOVE_UNIT, vec3d_norm((t_vec3d){{
				self->action.left - self->action.right,
				self->action.down - self->action.up,
				self->action.backward - self->action.forward,
			}}));

	if (!vec3d_abs(movement))
		return ;
	camera_move(self->camera, &movement);
	self->iter = -1;
}

static inline void	route(t_renderer *self)
{
	float	roll;
	float	pitch;
	float	yaw;
	float	unit;
	int		pos[2];

	roll = atan2(MOVE_UNIT * (self->action.roll_up - self->action.roll_dn), \
		ROTATION_RADIUS);
	pitch = atan2(MOVE_UNIT * (self->action.pitch_up - self->action.pitch_dn), \
		ROTATION_RADIUS);
	yaw = atan2(MOVE_UNIT * (self->action.yaw_up - self->action.yaw_dn), \
		ROTATION_RADIUS);
	if (self->action.mouse)
	{
		unit = self->camera->fov / self->camera->width;
		mlx_mouse_get_pos(self->mlx, self->win, &pos[0], &pos[1]);
		yaw -= (self->current_pos[0] - pos[0]) * unit;
		pitch -= (self->current_pos[1] - pos[1]) * unit;
		ft_memcpy(self->current_pos, pos, sizeof(pos));
	}
	if (!roll && !pitch && !yaw)
		return ;
	camera_rotate(self->camera, roll, pitch, yaw);
	self->iter = -1;
}

static inline void	set_fov(t_renderer *self)
{
	float	tmp;

	tmp = self->action.broaden - self->action.narrow;
	if (!tmp)
		return ;
	camera_set_fov(self->camera, ft_deg2rad(tmp) + self->camera->fov);
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
	set_fov(self);
	route(self);
	move(self);
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
