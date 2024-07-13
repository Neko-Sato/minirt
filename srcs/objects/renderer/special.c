/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 05:31:52 by hshimizu          #+#    #+#             */
/*   Updated: 2024/07/13 16:21:00 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects/renderer.h"
#include "constants.h"
#include "rt_errno.h"
#include <mlx.h>
#include <math.h>

t_rt_errno	renderer_init(t_renderer *self, t_renderer_init *args)
{
	*self = (t_renderer){};
	self->mlx = args->mlx;
	self->camera = args->camera;
	self->scene = args->scene;
	self->box[0] = self->camera->width / sqrt(PIXELS_PER_DRAW);
	self->box[1] = self->camera->height / sqrt(PIXELS_PER_DRAW);
	self->preview_box[0] = self->camera->width / sqrt(PIXELS_PER_DRAW_PREVIEW);
	self->preview_box[1] = self->camera->height / sqrt(PIXELS_PER_DRAW_PREVIEW);
	self->save = *args->camera;
	self->win = mlx_new_window(self->mlx, self->camera->width,
			self->camera->height, self->scene->title);
	if (!self->win)
		return (FAILED_ALLOCATE);
	self->img = mlx_new_image(self->mlx, self->camera->width,
			self->camera->height);
	if (!self->img)
		return (renderer_del(self), FAILED_ALLOCATE);
	renderer_set_hook(self);
	renderer_set_hook2(self);
	mlx_string_put(self->mlx, self->win, self->camera->width / 2,
		self->camera->height / 2, 0xFFFFFF, "now rendering...");
	return (SUCCESS);
}

void	renderer_del(t_renderer *self)
{
	if (self->img)
		mlx_destroy_image(self->mlx, self->img);
	if (self->win)
		mlx_destroy_window(self->mlx, self->win);
}
