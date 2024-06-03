/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 05:18:32 by hshimizu          #+#    #+#             */
/*   Updated: 2024/06/04 02:14:20 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects/scene.h"
#include "parser.h"
#include "rt_errno.h"
#include <fcntl.h>
#include <stdlib.h>

const t_class_scene	g_class_scene = {
	.init = __scene_init,
	.del = __scene_del,
	.load = __scene_load,
	.drawing = __scene_drawing,
	.set_ambient = __scene_set_ambient,
	.set_camera = __scene_set_camera,
	.add_light = __scene_add_light,
	.add_figure = __scene_add_figure,
};

int	__scene_init(t_scene *self, char *filename)
{
	int		ret;
	char	*title;

	*self = (t_scene){};
	self->__class = &g_class_scene;
	title = ft_strrchr(filename, '/');
	if (!title)
		title = filename;
	else
		title++;
	ft_strlcpy(self->title, title, sizeof(self->title));
	self->ambient = NULL;
	self->camera = NULL;
	self->lights = NULL;
	self->figures = NULL;
	ret = __scene_load(self, filename);
	if (ret)
		return (self->__class->del(self), ret);
	return (NO_ERROR);
}

void	__scene_del(t_scene *self)
{
	t_light		*light;
	t_figure	*figure;

	if (self->ambient)
		self->ambient->__class->del(self->ambient);
	free(self->ambient);
	if (self->camera)
		self->camera->__class->del(self->camera);
	free(self->camera);
	while (ft_xlstappend(&self->lights, &light, sizeof(light)))
	{
		light->__class->del(light);
		free(light);
	}
	while (ft_xlstappend(&self->figures, &figure, sizeof(figure)))
	{
		figure->__class->del(figure);
		free(figure);
	}
}

int	__scene_load(t_scene *self, char *filename)
{
	int		ret;
	t_file	*f;
	char	*line;
	size_t	size;
	char	*s;

	f = ft_file_new(open(filename, O_RDONLY), 0b10, 0, 1);
	if (!f)
		return (FAILED_OPEN);
	line = NULL;
	while (ft_getline(&line, &size, f) > 0)
	{
		s = line;
		ret = take_line(&s, self);
		if (ret)
			break ;
	}
	if (ret)
		return (ft_fclose(f), ret);
	if (ft_ferror(f))
		return (ft_fclose(f), FAILED_READ);
	if (ft_feof(f))
		return (ft_fclose(f), NO_ERROR);
	return (ft_fclose(f), FAILED_ALLOCATE);
}

void	__scene_drawing(t_scene *scene, unsigned int *data, int width,
		int height)
{
	(void)scene;
	(void)data;
	(void)width;
	(void)height;
}
