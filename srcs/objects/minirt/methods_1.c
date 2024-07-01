/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   methods_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 04:30:46 by hshimizu          #+#    #+#             */
/*   Updated: 2024/06/28 18:21:10 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects/minirt.h"
#include "objects/renderer.h"
#include "objects/scene.h"
#include "rt_errno.h"
#include <libft.h>
#include <stdlib.h>

static t_rt_errno	add_renderers(t_minirt *self, t_xlst **renderers,
						t_scene *scene);
static void			del_renderers(t_xlst **renderers);

t_rt_errno	minirt_add_scene(t_minirt *self, t_scene *scene)
{
	t_rt_errno	ret;
	t_xlst		*renderers;

	if (!ALLOW_MULTIPLE_CAMERAS && scene->cameras->next)
		return (MULTIPLE_DEFINED_CAMERA);
	if (!ALLOW_MULTIPLE_AMIBIENTS && scene->ambients->next)
		return (MULTIPLE_DEFINED_AMBIENT);
	renderers = NULL;
	ret = add_renderers(self, &renderers, scene);
	if (ret)
		return (del_renderers(&renderers), ret);
	if (ft_xlstappend(&self->scenes, &scene, sizeof(scene)))
		return (del_renderers(&renderers), FAILED_ALLOCATE);
	ft_xlstcat(&self->renderers, &renderers);
	return (SUCCESS);
}

static t_rt_errno	add_renderers(t_minirt *self, t_xlst **renderers,
		t_scene *scene)
{
	t_rt_errno	ret;
	t_xlst		*tmp;
	t_camera	*camera;
	t_renderer	*renderer;

	tmp = scene->cameras;
	while (tmp)
	{
		camera = *(t_camera **)tmp->data;
		renderer = malloc(sizeof(t_renderer));
		if (!renderer)
			return (FAILED_ALLOCATE);
		ret = renderer_init(renderer,
				&(t_renderer_init){
				.mlx = self->mlx,
				.camera = camera,
				.scene = scene,
			});
		if (ret)
			return (free(renderer), ret);
		if (ft_xlstappend(renderers, &renderer, sizeof(renderer)))
			return (renderer_del(renderer), free(renderer), FAILED_ALLOCATE);
		tmp = tmp->next;
	}
	return (SUCCESS);
}

static void	del_renderers(t_xlst **renderers)
{
	t_renderer	*renderer;

	while (!ft_xlstpop(renderers, 0, &renderer, sizeof(renderer)))
		(void)(renderer_del(renderer), free(renderer));
}
