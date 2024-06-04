/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 05:18:32 by hshimizu          #+#    #+#             */
/*   Updated: 2024/06/04 23:21:45 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects/scene.h"
#include "parser.h"
#include "rt_errno.h"
#include <fcntl.h>
#include <stdlib.h>

int	scene_init(t_scene *self, char *filename)
{
	int		ret;
	char	*title;

	*self = (t_scene){};
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
	ret = scene_load(self, filename);
	if (ret)
		return (scene_del(self), ret);
	return (NO_ERROR);
}

void	scene_del(t_scene *self)
{
	t_light		*light;
	t_figure	*figure;

	if (self->ambient)
		ambient_del(self->ambient);
	free(self->ambient);
	if (self->camera)
		camera_del(self->camera);
	free(self->camera);
	while (ft_xlstpop(&self->lights, 0, &light, sizeof(light)) != -1)
	{
		light_del(light);
		free(light);
	}
	while (ft_xlstpop(&self->figures, 0, &figure, sizeof(figure)) != -1)
	{
		figure_del(figure);
		free(figure);
	}
}

int	scene_load(t_scene *self, char *filename)
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
	free(line);
	if (ret)
		return (ft_fclose(f), ret);
	if (ft_ferror(f))
		return (ft_fclose(f), FAILED_READ);
	if (ft_feof(f))
		return (ft_fclose(f), NO_ERROR);
	return (ft_fclose(f), FAILED_ALLOCATE);
}

void	scene_drawing(t_scene *scene, unsigned int *data, int width, int height)
{
	(void)scene;
	(void)data;
	(void)width;
	(void)height;
}
