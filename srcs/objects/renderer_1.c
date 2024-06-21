/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer_1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 14:32:32 by hshimizu          #+#    #+#             */
/*   Updated: 2024/06/22 00:48:59 by hshimizu         ###   ########.fr       */
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
	self->iter = 0;
	return (0);
}

static int	keypress_hook(int keycode, t_renderer *self)
{
	if (keycode == XK_Escape)
		destroy_window(self);
	self->action.reset |= (keycode == XK_r);
	self->action.forward |= (keycode == XK_Up);
	self->action.backward |= (keycode == XK_Down);
	self->action.left |= (keycode == XK_Left);
	self->action.right |= (keycode == XK_Right);
	self->action.up |= (keycode == XK_z);
	self->action.down |= (keycode == XK_c);
	self->action.roll_up |= (keycode == XK_q);
	self->action.roll_dn |= (keycode == XK_e);
	self->action.pitch_up |= (keycode == XK_w);
	self->action.pitch_dn |= (keycode == XK_s);
	self->action.yaw_up |= (keycode == XK_a);
	self->action.yaw_dn |= (keycode == XK_d);
	self->action.broaden |= (keycode == XK_j);
	self->action.narrow |= (keycode == XK_k);
	return (0);
}

static int	keyrelease_hook(int keycode, t_renderer *self)
{
	self->action.forward &= (keycode != XK_Up);
	self->action.backward &= (keycode != XK_Down);
	self->action.left &= (keycode != XK_Left);
	self->action.right &= (keycode != XK_Right);
	self->action.up &= (keycode != XK_z);
	self->action.down &= (keycode != XK_c);
	self->action.roll_up &= (keycode != XK_q);
	self->action.roll_dn &= (keycode != XK_e);
	self->action.pitch_up &= (keycode != XK_w);
	self->action.pitch_dn &= (keycode != XK_s);
	self->action.yaw_up &= (keycode != XK_a);
	self->action.yaw_dn &= (keycode != XK_d);
	self->action.broaden &= (keycode != XK_j);
	self->action.narrow &= (keycode != XK_k);
	return (0);
}
