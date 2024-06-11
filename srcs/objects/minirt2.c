/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 04:30:46 by hshimizu          #+#    #+#             */
/*   Updated: 2024/06/11 20:42:58 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects/minirt.h"
#include "objects/renderer.h"
#include "objects/scene.h"
#include "rt_errno.h"
#include <stdlib.h>

/*
	I feel dirty here, so I think it needs to be fixed.
*/

static inline int		add_renderers(t_minirt *self, t_xlst **renderers,
							t_scene *scene);
static inline void	del_renderers(t_xlst **renderers);

int	minirt_add_scene(t_minirt *self, t_scene *scene)
{
	int		ret;
	t_xlst	*renderers;

	if (!ALLOW_MULTIPLE_CAMERAS && scene->cameras->next)
		return (MULTIPLE_DEFINED_CAMERA);
	if (!ALLOW_MULTIPLE_AMIBIENTS && scene->objs.ambients->next)
		return (MULTIPLE_DEFINED_AMBIENT);
	renderers = NULL;
	ret = add_renderers(self, &renderers, scene);
	if (ret)
		return (del_renderers(&renderers), ret);
	if (ft_xlstappend(&self->scenes, &scene, sizeof(scene)))
		return (del_renderers(&renderers), FAILED_ALLOCATE);
	ft_xlstcat(&self->renderers, &renderers);
	return (NO_ERROR);
}

static inline int	add_renderers(t_minirt *self, t_xlst **renderers,
		t_scene *scene)
{
	int			ret;
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
		ret = renderer_init(renderer, &(t_renderer_init){self->mlx,
				scene->title, camera, &scene->objs});
		if (ret)
			return (free(renderer), ret);
		if (ft_xlstappend(renderers, &renderer, sizeof(renderer)))
			return (renderer_del(renderer), free(renderer), FAILED_ALLOCATE);
		tmp = tmp->next;
	}
	return (NO_ERROR);
}

static inline void	del_renderers(t_xlst **renderers)
{
	t_renderer	*renderer;

	while (ft_xlstpop(renderers, 0, &renderer, sizeof(renderer)) != -1)
	{
		renderer_del(renderer);
		free(renderer);
	}
}
