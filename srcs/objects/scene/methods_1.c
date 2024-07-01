/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   methods_1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 05:29:48 by hshimizu          #+#    #+#             */
/*   Updated: 2024/06/28 22:15:51 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects/scene.h"
#include "rt_errno.h"
#include <libft.h>

t_rt_errno	scene_add_ambient(t_scene *self, t_ambient *ambient)
{
	if (ft_xlstappend(&self->ambients, &ambient, sizeof(ambient)))
		return (FAILED_ALLOCATE);
	return (SUCCESS);
}

t_rt_errno	scene_add_camera(t_scene *self, t_camera *camera)
{
	if (ft_xlstappend(&self->cameras, &camera, sizeof(camera)))
		return (FAILED_ALLOCATE);
	return (SUCCESS);
}

t_rt_errno	scene_add_light(t_scene *self, t_light *light)
{
	if (ft_xlstappend(&self->lights, &light, sizeof(light)))
		return (FAILED_ALLOCATE);
	return (SUCCESS);
}

t_rt_errno	scene_add_figure(t_scene *self, t_figure *figure)
{
	if (ft_xlstappend(&self->figures, &figure, sizeof(figure)))
		return (FAILED_ALLOCATE);
	return (SUCCESS);
}
