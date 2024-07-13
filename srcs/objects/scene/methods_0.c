/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   methods_0.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 05:29:48 by hshimizu          #+#    #+#             */
/*   Updated: 2024/07/14 03:50:19 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects/scene.h"
#include "objects/abstract_figure.h"
#include "objects/abstract_light.h"
#include "utils/ray.h"
#include <libft.h>

t_abstract_figure	*scene_get_nearest(t_scene *self, const t_ray *ray,
		float max_dist, float *dist)
{
	t_abstract_figure	*figure;
	size_t				i;
	t_abstract_figure	*nearest;
	float				t;

	nearest = NULL;
	i = 0;
	while (i < self->figures_size)
	{
		figure = self->figures[i++];
		if (figure->_->intersect(figure, ray, max_dist, &t))
		{
			nearest = figure;
			max_dist = t;
		}
	}
	if (nearest)
		*dist = t;
	return (nearest);
}

t_color	scene_get_intensity(t_scene *self, const t_ray *normal)
{
	t_abstract_light	*light;
	size_t				i;
	t_color				intensity;

	intensity.raw = COLOR_RAW_BLACK;
	i = 0;
	while (i < self->lights_size)
	{
		light = self->lights[i++];
		intensity = ft_color_add(\
			intensity, light->_->get_intensity(light, self, normal));
	}
	return (intensity);
}
