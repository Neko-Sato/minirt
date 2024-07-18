/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   methods_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 14:32:32 by hshimizu          #+#    #+#             */
/*   Updated: 2024/07/18 23:21:30 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects/renderer.h"
#include <X11/X.h>
#include <X11/keysym.h>
#include <mlx.h>

static int	keypress_hook(int keycode, t_renderer *self);
static int	keyrelease_hook(int keycode, t_renderer *self);
static int	buttonpress_hook(unsigned int button, int x, int y,
				t_renderer *self);
static int	buttonrelease_hook(unsigned int button, int x, int y,
				t_renderer *self);

void	renderer_set_hook2(t_renderer *self)
{
	mlx_hook(self->win, KeyPress, KeyPressMask, keypress_hook, self);
	mlx_hook(self->win, KeyRelease, KeyReleaseMask, keyrelease_hook, self);
	mlx_hook(self->win, ButtonPress, ButtonPressMask, buttonpress_hook, self);
	mlx_hook(self->win, ButtonRelease, ButtonReleaseMask, buttonrelease_hook,
		self);
}

static int	keypress_hook(int keycode, t_renderer *self)
{
	if (keycode == XK_Escape)
		renderer_destroy_window(self);
	self->action.reset |= (keycode == XK_r);
	self->action.forward |= (keycode == XK_w);
	self->action.backward |= (keycode == XK_s);
	self->action.left |= (keycode == XK_a);
	self->action.right |= (keycode == XK_d);
	self->action.up |= (keycode == XK_c);
	self->action.down |= (keycode == XK_z);
	self->action.roll_up |= (keycode == XK_q);
	self->action.roll_dn |= (keycode == XK_e);
	self->action.pitch_up |= (keycode == XK_Up);
	self->action.pitch_dn |= (keycode == XK_Down);
	self->action.yaw_up |= (keycode == XK_Left);
	self->action.yaw_dn |= (keycode == XK_Right);
	self->action.broaden |= (keycode == XK_j);
	self->action.narrow |= (keycode == XK_k);
	return (0);
}

static int	keyrelease_hook(int keycode, t_renderer *self)
{
	self->action.forward &= (keycode != XK_w);
	self->action.backward &= (keycode != XK_s);
	self->action.left &= (keycode != XK_a);
	self->action.right &= (keycode != XK_d);
	self->action.up &= (keycode != XK_c);
	self->action.down &= (keycode != XK_z);
	self->action.roll_up &= (keycode != XK_q);
	self->action.roll_dn &= (keycode != XK_e);
	self->action.pitch_up &= (keycode != XK_Up);
	self->action.pitch_dn &= (keycode != XK_Down);
	self->action.yaw_up &= (keycode != XK_Left);
	self->action.yaw_dn &= (keycode != XK_Right);
	self->action.broaden &= (keycode != XK_j);
	self->action.narrow &= (keycode != XK_k);
	return (0);
}

static int	buttonpress_hook(unsigned int button, int x, int y,
		t_renderer *self)
{
	if (button == Button1)
	{
		self->action.mouse |= 1;
		mlx_mouse_hide(self->mlx, self->win);
		self->current_pos[0] = x;
		self->current_pos[1] = y;
	}
	return (0);
}

static int	buttonrelease_hook(unsigned int button, int x, int y,
		t_renderer *self)
{
	if (button == Button1)
	{
		self->action.mouse &= 0;
		mlx_mouse_show(self->mlx, self->win);
		(void)x;
		(void)y;
	}
	return (0);
}
