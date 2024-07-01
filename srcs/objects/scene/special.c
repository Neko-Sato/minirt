/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 05:18:32 by hshimizu          #+#    #+#             */
/*   Updated: 2024/07/02 01:00:58 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects/scene.h"
#include "rt_errno.h"
#include <stdlib.h>
#include <libft.h>
#include <unistd.h>

t_rt_errno	scene_init(t_scene *self, t_scene_init *args)
{
	*self = (t_scene){};
	self->title = ft_strdup(args->title);
	if (!self->title)
		return (FAILED_ALLOCATE);
	return (SUCCESS);
}

void	scene_del(t_scene *self)
{
	void	*tmp;

	while (ft_xlstpop(&self->ambients, 0, &tmp, sizeof(t_ambient *)) != -1)
		(void)(ambient_del((t_ambient *)tmp), free(tmp));
	while (ft_xlstpop(&self->cameras, 0, &tmp, sizeof(t_camera *)) != -1)
		(void)(camera_del((t_camera *)tmp), free(tmp));
	while (ft_xlstpop(&self->lights, 0, &tmp, sizeof(t_light *)) != -1)
		(void)(light_del((t_light *)tmp), free(tmp));
	while (ft_xlstpop(&self->figures, 0, &tmp, sizeof(t_figure *)) != -1)
		(void)(((t_figure *)tmp)->_->del(((t_figure *)tmp)), free(tmp));
	free(self->title);
}
