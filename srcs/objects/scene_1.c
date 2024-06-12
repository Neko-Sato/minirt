/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 05:29:48 by hshimizu          #+#    #+#             */
/*   Updated: 2024/06/12 12:37:06 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects/scene.h"
#include "rt_errno.h"
#include <libft.h>

int	scene_add_ambient(t_scene *self, t_ambient *ambient)
{
	if (ft_xlstappend(&self->objs.ambients, &ambient, sizeof(ambient)))
		return (FAILED_ALLOCATE);
	return (NO_ERROR);
}

int	scene_add_camera(t_scene *self, t_camera *camera)
{
	if (ft_xlstappend(&self->cameras, &camera, sizeof(camera)))
		return (FAILED_ALLOCATE);
	return (NO_ERROR);
}

int	scene_add_light(t_scene *self, t_light *light)
{
	if (ft_xlstappend(&self->objs.lights, &light, sizeof(light)))
		return (FAILED_ALLOCATE);
	return (NO_ERROR);
}

int	scene_add_figure(t_scene *self, t_figure *figure)
{
	if (ft_xlstappend(&self->objs.figures, &figure, sizeof(figure)))
		return (FAILED_ALLOCATE);
	return (NO_ERROR);
}
