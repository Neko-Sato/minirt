/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer_3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 16:17:05 by hshimizu          #+#    #+#             */
/*   Updated: 2024/06/16 15:00:54 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects/renderer.h"
#include "rt_errno.h"
#include "utils/matrix3x3.h"
#include "utils/vec3d.h"

static inline void	move(t_renderer *self)
{
	t_vec3d	movement;

	movement = (t_vec3d){{0, 0, 0}};
	if (self->action.move_forward && !self->action.move_backward)
		movement._[2] = MOVE_UNIT;
	else if (!self->action.move_forward && self->action.move_backward)
		movement._[2] = -MOVE_UNIT;
	if (self->action.move_left && !self->action.move_right)
		movement._[0] = -MOVE_UNIT;
	else if (!self->action.move_left && self->action.move_right)
		movement._[0] = MOVE_UNIT;
	if (self->action.move_up && !self->action.move_down)
		movement._[1] = MOVE_UNIT;
	else if (!self->action.move_up && self->action.move_down)
		movement._[1] = -MOVE_UNIT;
	if (movement._[0] || movement._[1] || movement._[2])
	{
		self->camera->coordinates = vec3d_add(self->camera->coordinates,
				matrix3x3_mul_vec3d(self->transform, movement));
		renderer_update_transform(self);
		self->iter = 0;
	}
}

static inline void	route_yaw(t_renderer *self)
{
	t_matrix3x3	rotation;
	float		n;

	if (self->action.look_left && !self->action.look_right)
		n = -ROTATE_UNIT;
	else if (!self->action.look_left && self->action.look_right)
		n = ROTATE_UNIT;
	else
		return ;
	rotation = matrix3x3_rotation_axis(n, matrix3x3_mul_vec3d(self->transform,
				(t_vec3d){{0, 1, 0}}));
	self->camera->orientation = matrix3x3_mul_vec3d(rotation,
			self->camera->orientation);
	renderer_update_transform(self);
	self->iter = 0;
}

static inline void	route_pitch(t_renderer *self)
{
	t_matrix3x3	rotation;
	t_vec3d		tmp;
	float		n;

	if (self->action.look_up && !self->action.look_down)
		n = -ROTATE_UNIT;
	else if (!self->action.look_up && self->action.look_down)
		n = ROTATE_UNIT;
	else
		return ;
	rotation = matrix3x3_rotation_axis(n, matrix3x3_mul_vec3d(self->transform,
				(t_vec3d){{1, 0, 0}}));
	tmp = matrix3x3_mul_vec3d(rotation, self->camera->orientation);
	if (self->camera->orientation._[0] < 0 && 0 <= tmp._[0])
		return ;
	else if (self->camera->orientation._[0] > 0 && 0 >= tmp._[0])
		return ;
	if (self->camera->orientation._[2] < 0 && 0 <= tmp._[2])
		return ;
	else if (self->camera->orientation._[2] > 0 && 0 >= tmp._[2])
		return ;
	self->camera->orientation = tmp;
	renderer_update_transform(self);
	self->iter = 0;
}

static inline void	action(t_renderer *self)
{
	if (self->action.reset)
	{
		self->action.reset = 0;
		self->camera->orientation = self->save_ray.o;
		self->camera->coordinates = self->save_ray.c;
		renderer_update_transform(self);
		self->iter = 0;
		return ;
	}
	move(self);
	route_yaw(self);
	route_pitch(self);
}

int	renderer_loop_hook(t_renderer *self)
{
	if (!self->focus)
		return (NO_ERROR);
	action(self);
	if (self->max_iter <= self->iter)
		return (NO_ERROR);
	return (renderer_render(self));
}
