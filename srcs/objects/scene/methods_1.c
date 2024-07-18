/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   methods_1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 05:29:48 by hshimizu          #+#    #+#             */
/*   Updated: 2024/07/19 00:06:21 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects/abstract_figure.h"
#include "objects/scene.h"
#include "utils/ray.h"
#include "constants.h"
#include <libft.h>

t_color	scene_trace(t_scene *self, const t_ray *ray, int max_depth)
{
	t_color				color;
	t_abstract_figure	*nearest;
	float				dist;
	t_ray				normal;

	color.raw = COLOR_RAW_BLACK;
	if (!max_depth)
		return (color);
	nearest = scene_get_nearest(self, ray, MAX_DIST, &dist);
	if (nearest)
	{
		normal = nearest->_->get_normal(nearest, dist, ray);
		color = nearest->_->get_color(nearest, &normal);
		color = ft_color_sub(color, scene_get_intensity(self, &normal));
		if (nearest->reflectivity)
			color = ft_color_add(
					ft_color_brightness(1 - nearest->reflectivity,
						color),
					ft_color_brightness(nearest->reflectivity,
						scene_trace(self, &(t_ray){vec3d_sub(ray->o, \
			vec3d_mul(2 * vec3d_dot(ray->o, normal.o), normal.o)), normal.c \
			}, max_depth - 1)));
	}
	return (color);
}

t_color	scene_rough_trace(t_scene *self, const t_ray *ray)
{
	t_abstract_figure	*nearest;

	nearest = scene_get_nearest(self, ray, MAX_DIST, &(float){0});
	if (nearest)
		return (nearest->color);
	return ((t_color){.raw = COLOR_RAW_BLACK});
}
