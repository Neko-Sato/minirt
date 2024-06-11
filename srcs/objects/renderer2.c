/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 14:32:32 by hshimizu          #+#    #+#             */
/*   Updated: 2024/06/11 19:05:08 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects/renderer.h"
#include <X11/X.h>
#include <X11/keysym.h>
#include <mlx.h>

static int	destroy_window(t_renderer *self);
static int	expose_hook(t_renderer *self);
static int	keypress_hook(int keycode, t_renderer *self);
static int	keyrelease_hook(int keycode, t_renderer *self);

void	renderer_set_hook(t_renderer *self)
{
	mlx_hook(self->win, DestroyNotify, StructureNotifyMask, destroy_window,
		self);
	mlx_hook(self->win, Expose, ExposureMask, expose_hook, self);
	mlx_hook(self->win, KeyPress, KeyPressMask, keypress_hook, self);
	mlx_hook(self->win, KeyRelease, KeyReleaseMask, keyrelease_hook, self);
}

static int	destroy_window(t_renderer *self)
{
	mlx_destroy_window(self->mlx, self->win);
	self->win = NULL;
	return (0);
}

//	mlx cannot handle changes to the screen ratio. Damn...
static int	expose_hook(t_renderer *self)
{
	self->needs_rendring = 1;
	return (0);
}

static int	keypress_hook(int keycode, t_renderer *self)
{
	if (keycode == XK_Escape)
		destroy_window(self);
	else if (keycode == XK_F5)
		self->needs_rendring = 1;
	else if (keycode == XK_Up)
		self->action.look_up = 1;
	else if (keycode == XK_Down)
		self->action.look_down = 1;
	else if (keycode == XK_Left)
		self->action.look_left = 1;
	else if (keycode == XK_Right)
		self->action.look_right = 1;
	else if (keycode == XK_w)
		self->action.move_forward = 1;
	else if (keycode == XK_x)
		self->action.move_backward = 1;
	else if (keycode == XK_a)
		self->action.move_left = 1;
	else if (keycode == XK_d)
		self->action.move_right = 1;
	else if (keycode == XK_q)
		self->action.move_up = 1;
	else if (keycode == XK_e)
		self->action.move_down = 1;
	return (0);
}

static int	keyrelease_hook(int keycode, t_renderer *self)
{
	if (keycode == XK_Up)
		self->action.look_up = 0;
	else if (keycode == XK_Down)
		self->action.look_down = 0;
	else if (keycode == XK_Left)
		self->action.look_left = 0;
	else if (keycode == XK_Right)
		self->action.look_right = 0;
	else if (keycode == XK_w)
		self->action.move_forward = 0;
	else if (keycode == XK_x)
		self->action.move_backward = 0;
	else if (keycode == XK_a)
		self->action.move_left = 0;
	else if (keycode == XK_d)
		self->action.move_right = 0;
	else if (keycode == XK_q)
		self->action.move_up = 0;
	else if (keycode == XK_e)
		self->action.move_down = 0;
	return (0);
}
