/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   methods_1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 04:30:46 by hshimizu          #+#    #+#             */
/*   Updated: 2024/07/14 03:17:21 by hshimizu         ###   ########.fr       */
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
	size_t		i;
	t_renderer	*renderer;

	i = 0;
	while (i < scene->cameras_size)
	{
		renderer = malloc(sizeof(t_renderer));
		if (!renderer)
			return (FAILED_ALLOCATE);
		ret = renderer_init(renderer,
				&(t_renderer_init){
				.mlx = self->mlx,
				.camera = scene->cameras[i],
				.scene = scene,
			});
		if (ret)
			return (free(renderer), ret);
		if (ft_xlstappend(renderers, &renderer, sizeof(renderer)))
			return (renderer_del(renderer), free(renderer), FAILED_ALLOCATE);
		i++;
	}
	return (SUCCESS);
}

static void	del_renderers(t_xlst **renderers)
{
	t_renderer	*renderer;

	while (!ft_xlstpop(renderers, 0, &renderer, sizeof(renderer)))
		(void)(renderer_del(renderer), free(renderer));
}
