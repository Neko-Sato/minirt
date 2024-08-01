/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   static_methods_0.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 03:01:06 by hshimizu          #+#    #+#             */
/*   Updated: 2024/08/01 19:23:46 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects/scene.h"
#include "parser.h"
#include <stdlib.h>

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
	return (scene_init(scene, &args));
}

static inline t_rt_errno	make_scene_init_internal(t_scene_init *args,
		t_parser_res *res)
{
	args->cameras = ft_xlst2array(res->cameras, sizeof(t_camera *),
			&args->cameras_size);
	if (!args->cameras)
		return (FAILED_ALLOCATE);
	args->lights = ft_xlst2array(res->lights, sizeof(t_camera *),
			&args->lights_size);
	if (!args->lights)
		return (FAILED_ALLOCATE);
	args->figures = ft_xlst2array(res->figures, sizeof(t_camera *),
			&args->figures_size);
	if (!args->figures)
		return (FAILED_ALLOCATE);
	return (SUCCESS);
}

static t_rt_errno	make_scene_init(char *filename, t_scene_init *args)
{
	t_rt_errno		ret;
	t_parser_res	res;
	void			*tmp;

	ret = parser(filename, &res);
	if (ret)
		return (ret);
	ret = make_scene_init_internal(args, &res);
	if (ret)
	{
		while (ft_xlstpop(&res.cameras, 0, &tmp, sizeof(tmp)) != -1)
			(void)(camera_del(tmp), free(tmp));
		while (ft_xlstpop(&res.lights, 0, &tmp, sizeof(tmp)) != -1)
			(void)(((t_abstract_light *)tmp)->_->del(tmp), free(tmp));
		while (ft_xlstpop(&res.figures, 0, &tmp, sizeof(tmp)) != -1)
			(void)(((t_abstract_figure *)tmp)->_->del(tmp), free(tmp));
	}
	else
	{
		ft_xlstclear(&res.cameras);
		ft_xlstclear(&res.lights);
		ft_xlstclear(&res.figures);
	}
	return (ret);
}
