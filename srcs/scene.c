/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 03:06:41 by hshimizu          #+#    #+#             */
/*   Updated: 2024/05/16 08:52:52 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <fcntl.h>
#include <libft.h>
#include <stdlib.h>

static int	load_rt_internal(t_scene *scene, t_bufferio *f);
static int	scene_set(t_scene *scene, t_object *object);
static int	scene_set2(t_scene *scene, t_object *object);

int	load_rt(t_scene *scene, char *filename)
{
	int			ret;
	t_bufferio	*f;

	*scene = (t_scene){};
	if (!ft_endwith(filename, ".rt"))
		return (NOT_RT_FILE);
	scene->title = ft_getfilename(filename);
	if (!scene->title)
		return (FAILED_ALLOCATE);
	f = ft_open(open(filename, O_RDONLY), 1);
	if (!f)
		return (scene_del(scene), FAILED_OPEN);
	ret = load_rt_internal(scene, f);
	if (ret)
		scene_del(scene);
	ft_close(f, 1);
	return (ret);
}

static int	load_rt_internal(t_scene *scene, t_bufferio *f)
{
	int			ret;
	char		*str;
	t_object	tmp;

	while (1)
	{
		if (ft_readline(&str, f))
			return (FAILED_ALLOCATE);
		if (!str)
			break ;
		ret = object_parser(str, &tmp);
		free(str);
		if (!ret)
			ret = scene_set(scene, &tmp);
		if (ret)
			return (ret);
	}
	if (!scene->ambient)
		return (UNDEFINED_AMBIENT);
	if (!scene->camera)
		return (UNDEFINED_CAMERA);
	return (NO_ERROR);
}

static int	scene_set(t_scene *scene, t_object *object)
{
	if (object->type == o_none)
		return (NO_ERROR);
	if (object->type == o_ambient)
	{
		if (scene->ambient)
			return (MULTIPLE_DEFINED_AMBIENT);
		scene->ambient = ft_memdup(&object->value.ambient, sizeof(t_o_ambient));
		if (!scene->ambient)
			return (FAILED_ALLOCATE);
		return (NO_ERROR);
	}
	if (object->type == o_camera)
	{
		if (scene->camera)
			return (MULTIPLE_DEFINED_CAMERA);
		scene->camera = ft_memdup(&object->value.camera, sizeof(t_o_camera));
		if (!scene->camera)
			return (FAILED_ALLOCATE);
		return (NO_ERROR);
	}
	return (scene_set2(scene, object));
}

static int	scene_set2(t_scene *scene, t_object *object)
{
	if (object->type == o_light)
	{
		if (ft_xlstappend(&scene->rights, &object->value.light,
				sizeof(t_o_light)))
			return (FAILED_ALLOCATE);
		return (NO_ERROR);
	}
	if (object->type == o_figure)
	{
		if (ft_xlstappend(&scene->figures, &object->value.figure,
				sizeof(t_o_figure)))
			return (FAILED_ALLOCATE);
		return (NO_ERROR);
	}
	return (UNLIKELY_ERROR);
}

void	scene_del(t_scene *scene)
{
	free(scene->title);
	free(scene->ambient);
	free(scene->camera);
	ft_xlstclear(&scene->rights);
	ft_xlstclear(&scene->figures);
	*scene = (t_scene){};
}
