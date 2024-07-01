/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   methods_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 05:29:48 by hshimizu          #+#    #+#             */
/*   Updated: 2024/06/29 01:26:30 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects/figure.h"
#include "objects/scene.h"
#include "utils/ray.h"
#include <libft.h>

t_figure	*scene_get_nearest(t_scene *scene, const t_ray *r, float max_dist,
		float *dist)
{
	t_xlst		*tmp;
	t_figure	*figrue;
	t_figure	*nearest;

	nearest = NULL;
	tmp = scene->figures;
	while (tmp)
	{
		figrue = *(t_figure **)tmp->data;
		if (figrue->_->intersect(figrue, r, max_dist, &max_dist))
			nearest = figrue;
		tmp = tmp->next;
	}
	*dist = max_dist;
	return (nearest);
}

t_color	scene_trace(t_scene *self, const t_ray *r, float max_dist,
		int max_depth)
{
	t_color		color;
	t_figure	*nearest;
	float		dist;
	t_vec3d		point;

	color.raw = COLOR_RAW_BLACK;
	if (!max_depth)
		return (color);
	nearest = scene_get_nearest(self, r, max_dist, &dist);
	if (nearest)
	{
		point = vec3d_add(vec3d_mul(dist, r->o), r->c);
		color = nearest->_->get_color(nearest, &point);
	}
	return (color);
}
