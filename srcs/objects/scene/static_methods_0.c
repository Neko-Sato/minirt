/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   static_methods_0.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 03:01:06 by hshimizu          #+#    #+#             */
/*   Updated: 2024/07/14 03:34:38 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects/scene.h"
#include "parser.h"

static t_rt_errno			make_scene_init(char *filename, t_scene_init *args);

t_rt_errno	scene_load(t_scene *scene, char *filename)
{
	t_rt_errno		ret;
	t_scene_init	args;

	if (!ft_endwith(filename, ".rt"))
		return (NOT_RT_FILE);
	args.title = ft_strrchr(filename, '/');
	if (args.title)
		args.title++;
	else
		args.title = filename;
	ret = make_scene_init(filename, &args);
	if (ret)
		return (ret);
	ret = scene_init(scene, &args);
	if (ret)
		return (ret);
	return (SUCCESS);
}

static inline t_rt_errno	make_scene_init_internal(t_scene_init *args,
		t_parser *context)
{
	args->cameras = ft_xlst2array(context->cameras, sizeof(t_camera *),
			&args->cameras_size);
	if (!args->cameras)
		return (FAILED_ALLOCATE);
	args->lights = ft_xlst2array(context->lights, sizeof(t_camera *),
			&args->lights_size);
	if (!args->lights)
		return (FAILED_ALLOCATE);
	args->figures = ft_xlst2array(context->figures, sizeof(t_camera *),
			&args->figures_size);
	if (!args->figures)
		return (FAILED_ALLOCATE);
	return (SUCCESS);
}

static t_rt_errno	make_scene_init(char *filename, t_scene_init *args)
{
	t_rt_errno	ret;
	t_parser	context;

	ret = parser(filename, &context);
	if (ret)
		return (ret);
	ret = make_scene_init_internal(args, &context);
	ft_xlstclear(&context.cameras);
	ft_xlstclear(&context.lights);
	ft_xlstclear(&context.figures);
	return (ret);
}
