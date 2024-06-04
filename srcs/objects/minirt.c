/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 03:57:27 by hshimizu          #+#    #+#             */
/*   Updated: 2024/06/05 03:07:33 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects/minirt.h"
#include "rt_errno.h"
#include <X11/X.h>
#include <X11/keysym.h>
#include <mlx.h>
#include <stdlib.h>

static int	loop_hook(t_minirt *self);
static int	key_hook(int keycode, t_minirt *self);
static int	destroy_window(t_minirt *self);

int	minirt_init(t_minirt *self, t_scene *scene, int width, int height)
{
	*self = (t_minirt){};
	self->mlx = mlx_init();
	if (!self->mlx)
		return (minirt_del(self), FAILED_INITIALIZE_MLX);
	self->win = mlx_new_window(self->mlx, width, height, scene->title);
	if (!self->win)
		return (minirt_del(self), FAILED_ALLOCATE);
	self->img = mlx_new_image(self->mlx, width, height);
	if (!self->img)
		return (minirt_del(self), FAILED_ALLOCATE);
	self->width = width;
	self->height = height;
	self->needs_rendering = 1;
	self->scene = scene;
	self->errno = NO_ERROR;
	mlx_string_put(self->mlx, self->win, width / 2, height / 2, 0xFFFFFF,
		"now rendering...");
	mlx_hook(self->win, DestroyNotify, NoEventMask, destroy_window, self);
	mlx_key_hook(self->win, key_hook, self);
	mlx_loop_hook(self->mlx, loop_hook, self);
	return (NO_ERROR);
}

void	minirt_del(t_minirt *self)
{
	if (self->img)
		mlx_destroy_image(self->mlx, self->img);
	if (self->win)
		mlx_destroy_window(self->mlx, self->win);
	if (self->mlx)
		mlx_destroy_display(self->mlx);
	free(self->mlx);
	if (self->scene)
		scene_del(self->scene);
	free(self->scene);
}

static int	loop_hook(t_minirt *self)
{
	if (self->needs_rendering)
	{
		self->errno = minirt_render(self);
		if (self->errno)
			return (mlx_loop_end(self->mlx), -1);
		self->needs_rendering = 0;
	}
	return (0);
}

static int	destroy_window(t_minirt *self)
{
	mlx_destroy_window(self->mlx, self->win);
	self->win = NULL;
	return (0);
}

static int	key_hook(int keycode, t_minirt *self)
{
	if (keycode == XK_Escape)
		destroy_window(self);
	else if (keycode == XK_F5)
		self->needs_rendering = 1;
	return (0);
}
