/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 05:29:48 by hshimizu          #+#    #+#             */
/*   Updated: 2024/06/02 05:36:20 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects/scene.h"
#include "rt_errno.h"
#include <libft.h>

int	__scene_set_ambient(t_scene *self, t_ambient *ambient)
{
	if (self->ambient)
		return (MULTIPLE_DEFINED_AMBIENT);
	self->ambient = ambient;
	return (NO_ERROR);
}

int	__scene_set_camera(t_scene *self, t_camera *camera)
{
	if (self->camera)
		return (MULTIPLE_DEFINED_CAMERA);
	self->camera = camera;
	return (NO_ERROR);
}

int	__scene_add_light(t_scene *self, t_light *light)
{
	if (ft_xlstappend(&self->lights, &light, sizeof(light)))
		return (FAILED_ALLOCATE);
	return (NO_ERROR);
}

int	__scene_add_figure(t_scene *self, t_figure *figure)
{
	if (ft_xlstappend(&self->figures, &figure, sizeof(figure)))
		return (FAILED_ALLOCATE);
	return (NO_ERROR);
}
