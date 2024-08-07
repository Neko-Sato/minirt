/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 05:18:32 by hshimizu          #+#    #+#             */
/*   Updated: 2024/07/25 01:37:27 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects/scene.h"
#include "objects/bvh.h"
#include "rt_errno.h"
#include <stdlib.h>
#include <libft.h>

t_rt_errno	scene_init(t_scene *self, t_scene_init *args)
{
	t_rt_errno	ret;

	*self = (t_scene){};
	if (!args->cameras_size)
		return (UNDEFINED_CAMERA);
	self->title = ft_strdup(args->title);
	if (!self->title)
		return (FAILED_ALLOCATE);
	self->cameras_size = args->cameras_size;
	self->cameras = args->cameras;
	self->lights_size = args->lights_size;
	self->lights = args->lights;
	self->figures_size = args->figures_size;
	self->figures = args->figures;
	ret = bvh_build(&self->bvh, self->figures, self->figures_size);
	if (ret)
		return (free(self->title), ret);
	return (SUCCESS);
}

static void	scene_del_internal(t_scene *self);

void	scene_del(t_scene *self)
{
	size_t	i;

	i = 0;
	while (i < self->cameras_size)
	{
		camera_del(self->cameras[i]);
		free(self->cameras[i]);
		i++;
	}
	free(self->cameras);
	i = 0;
	while (i < self->lights_size)
	{
		self->lights[i]->_->del(self->lights[i]);
		free(self->lights[i]);
		i++;
	}
	free(self->lights);
	return (scene_del_internal(self));
}

static void	scene_del_internal(t_scene *self)
{
	size_t	i;

	self->bvh->_->del(self->bvh);
	free(self->bvh);
	i = 0;
	while (i < self->figures_size)
	{
		self->figures[i]->_->del(self->figures[i]);
		free(self->figures[i]);
		i++;
	}
	free(self->figures);
	free(self->title);
}
