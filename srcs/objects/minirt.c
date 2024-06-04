/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 03:57:27 by hshimizu          #+#    #+#             */
/*   Updated: 2024/06/05 07:03:55 by hshimizu         ###   ########.fr       */
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

int	minirt_init(t_minirt *self, t_scene *scene)
{
	*self = (t_minirt){};
	if (!scene->ambient)
		return (minirt_del(self), UNDEFINED_AMBIENT);
	if (!scene->camera)
		return (minirt_del(self), UNDEFINED_CAMERA);
	self->mlx = mlx_init();
	if (!self->mlx)
		return (minirt_del(self), FAILED_INITIALIZE_MLX);
	self->win = mlx_new_window(self->mlx, scene->camera->width,
			scene->camera->height, scene->title);
	if (!self->win)
		return (minirt_del(self), FAILED_ALLOCATE);
	self->img = mlx_new_image(self->mlx, scene->camera->width,
			scene->camera->height);
	if (!self->img)
		return (minirt_del(self), FAILED_ALLOCATE);
	self->scene = scene;
	self->needs_rendering = 1;
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
		mlx_clear_window(self->mlx, self->win);
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
