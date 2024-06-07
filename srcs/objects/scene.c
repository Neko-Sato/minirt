/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 05:18:32 by hshimizu          #+#    #+#             */
/*   Updated: 2024/06/07 16:53:18 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects/scene.h"
#include "parser.h"
#include "rt_errno.h"
#include "utils/matrix3x3.h"
#include "utils/vec3d.h"
#include <fcntl.h>
#include <stdlib.h>

int	scene_init(t_scene *self, char *title)
{
	*self = (t_scene){};
	ft_strlcpy(self->title, title, sizeof(self->title));
	self->ambient = NULL;
	self->camera = NULL;
	self->lights = NULL;
	self->figures = NULL;
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
		figure->__vtable->del(figure);
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

int	scene_move(t_scene *self, long double leftright, long double updown,
		long double frontback)
{
	const t_vec3d		f = vec3d_norm(self->camera->orientation);
	const t_vec3d		r = vec3d_norm(vec3d_cross((t_vec3d){{0, 1, 0}}, f));
	const t_vec3d		u = vec3d_norm(vec3d_cross(f, r));
	t_vec3d				tmp;

	tmp = vec3d_add(vec3d_add(
				vec3d_mul(leftright, r),
				vec3d_mul(updown, u)),
			vec3d_mul(frontback, f));
	self->camera->coordinates = vec3d_add(self->camera->coordinates, tmp);
	return (0);
}

int	scene_rotate(t_scene *self, long double updown, long double leftright)
{
	const t_vec3d		f = vec3d_norm(self->camera->orientation);
	const t_vec3d		r = vec3d_norm(vec3d_cross((t_vec3d){{0, 1, 0}}, f));
	const t_vec3d		u = vec3d_norm(vec3d_cross(f, r));
	const t_matrix3x3	rotation = matrix3x3_mul(
			matrix3x3_rotation_axis(leftright, u),
			matrix3x3_rotation_axis(updown, r));
	t_vec3d				tmp;

	tmp = matrix3x3_mul_vec3d(rotation, f);
	if (updown)
	{
		if (self->camera->orientation._[0] < 0 && 0 <= tmp._[0])
			return (1);
		else if (self->camera->orientation._[0] > 0 && 0 >= tmp._[0])
			return (1);
		if (self->camera->orientation._[2] < 0 && 0 <= tmp._[2])
			return (1);
		else if (self->camera->orientation._[2] > 0 && 0 >= tmp._[2])
			return (1);
	}
	self->camera->orientation = tmp;
	return (0);
}
