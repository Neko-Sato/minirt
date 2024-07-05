/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   methods_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 05:29:48 by hshimizu          #+#    #+#             */
/*   Updated: 2024/07/05 21:03:51 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects/figure.h"
#include "objects/scene.h"
#include "utils/ray.h"
#include <libft.h>

t_color	scene_trace(t_scene *self, const t_ray *r, float max_dist,
		int max_depth)
{
	t_color		color;
	t_color		light;
	t_figure	*nearest;
	float		dist;
	t_ray		normal;

	color.raw = COLOR_RAW_BLACK;
	light.raw = COLOR_RAW_BLACK;
	if (!max_depth)
		return (color);
	nearest = scene_get_nearest(self, r, max_dist, &dist);
	if (nearest)
	{
		normal = nearest->_->get_normal(nearest, dist, r);
		color = nearest->_->get_color(nearest, &normal);
		scene_apply_lights(self, &normal, &light);
		scene_apply_ambients(self, &light);
		color = ft_color_sub(color, light);
	}
	return (color);
}

t_color	scene_rough_trace(t_scene *self, const t_ray *r, float max_dist)
{
	t_figure	*nearest;

	nearest = scene_get_nearest(self, r, max_dist, &(float){0});
	if (nearest)
		return (nearest->color);
	return ((t_color){.raw = COLOR_RAW_BLACK});
}
