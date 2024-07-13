/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   methods_1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 05:29:48 by hshimizu          #+#    #+#             */
/*   Updated: 2024/07/14 04:22:07 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects/abstract_figure.h"
#include "objects/scene.h"
#include "utils/ray.h"
#include <libft.h>

t_color	scene_trace(t_scene *self, const t_ray *ray, float max_dist,
		int max_depth)
{
	t_color				color;
	t_abstract_figure	*nearest;
	float				dist;
	t_ray				normal;

	color.raw = COLOR_RAW_BLACK;
	if (!max_depth)
		return (color);
	nearest = scene_get_nearest(self, ray, max_dist, &dist);
	if (nearest)
	{
		normal = nearest->_->get_normal(nearest, dist, ray);
		color = nearest->_->get_color(nearest, &normal);
		color = ft_color_sub(color, scene_get_intensity(self, &normal));
		if (nearest->texture.reflectivity)
			color = ft_color_add(
					ft_color_brightness(1 - nearest->texture.reflectivity,
						color),
					ft_color_brightness(nearest->texture.reflectivity,
						scene_trace(self, &normal, max_dist, max_depth - 1)));
	}
	return (color);
}

t_color	scene_rough_trace(t_scene *self, const t_ray *ray, float max_dist)
{
	t_abstract_figure	*nearest;

	nearest = scene_get_nearest(self, ray, max_dist, &(float){0});
	if (nearest)
		return (nearest->texture.color);
	return ((t_color){.raw = COLOR_RAW_BLACK});
}
