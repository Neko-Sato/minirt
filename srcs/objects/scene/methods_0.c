/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   methods_0.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 05:29:48 by hshimizu          #+#    #+#             */
/*   Updated: 2024/07/24 11:57:11 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects/abstract_figure.h"
#include "objects/abstract_light.h"
#include "objects/scene.h"
#include "utils/ray.h"
#include "constants.h"
#include <libft.h>

t_abstract_figure	*scene_get_nearest(t_scene *self, const t_ray *ray,
		float max_dist, float *dist)
{
	size_t				i;
	t_abstract_figure	*figure;
	t_abstract_figure	*nearest;
	float				t;

	nearest = NULL;
	i = 0;
	while (i < self->figures_size)
	{
		figure = self->figures[i++];
		if (!figure->_->intersect(figure, ray, max_dist, &t))
			continue ;
		nearest = figure;
		max_dist = t;
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
		intensity = ft_color_add(intensity, \
			light->_->get_intensity(light, self, normal));
	}
	return (intensity);
}

t_color	scene_trace(t_scene *self, const t_ray *ray, int max_depth)
{
	t_color				color;
	t_abstract_figure	*nearest;
	float				dist;
	t_vec3				point;
	t_vec3				normal;

	nearest = scene_get_nearest(self, ray, MAX_DIST, &dist);
	if (!nearest)
		return ((t_color){.raw = COLOR_RAW_BLACK});
	if (max_depth < 0)
		return (nearest->color);
	point = vec3_add(ray->c, vec3_mul(dist, ray->o));
	color = abstract_figure_get_color(nearest, &point);
	normal = nearest->_->get_normal(nearest, &point);
	if (vec3_dot(normal, ray->o) > 0)
		normal = vec3_mul(-1, normal);
	color = ft_color_sub(color, \
		scene_get_intensity(self, &(t_ray){normal, point}));
	if (0 < max_depth && nearest->reflectivity)
		color = ft_color_add(\
			ft_color_brightness(1 - nearest->reflectivity, color), \
			ft_color_brightness(nearest->reflectivity, \
				scene_trace(self, &(t_ray){\
					vec3_reflect(ray->o, normal), point}, max_depth - 1)));
	return (color);
}
