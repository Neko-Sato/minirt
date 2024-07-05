/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   methods_3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 05:29:48 by hshimizu          #+#    #+#             */
/*   Updated: 2024/07/06 00:44:06 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects/figure.h"
#include "objects/scene.h"
#include "utils/ray.h"
#include <libft.h>
#include <math.h>

t_figure	*scene_get_nearest(t_scene *self, const t_ray *r, float max_dist,
		float *dist)
{
	t_xlst		*tmp;
	t_figure	*figrue;
	t_figure	*nearest;
	float		t;

	nearest = NULL;
	tmp = self->figures;
	while (tmp)
	{
		figrue = *(t_figure **)tmp->data;
		if (figrue->_->intersect(figrue, r, max_dist, &t))
		{
			if (1 < t)
			{
				nearest = figrue;
				max_dist = t;
			}
		}
		tmp = tmp->next;
	}
	*dist = max_dist;
	return (nearest);
}

void	scene_apply_ambients(t_scene *self, t_color *color)
{
	t_xlst		*tmp;
	t_ambient	*ambient;

	tmp = self->ambients;
	while (tmp)
	{
		ambient = *(t_ambient **)tmp->data;
		*color = ft_color_add(*color, ambient->color);
		tmp = tmp->next;
	}
}

void	scene_apply_lights(t_scene *self, const t_ray *normal, t_color *color)
{
	t_xlst	*tmp;
	t_light	*light;
	t_vec3d	v;
	float	n;

	tmp = self->lights;
	while (tmp)
	{
		light = *(t_light **)tmp->data;
		v = vec3d_sub(light->coord, normal->c);
		n = vec3d_dot(vec3d_norm(v), normal->o);
		if (0 < n && !scene_get_nearest(self, &(t_ray){vec3d_norm(v),
				normal->c}, vec3d_abs(v), &(float){0}))
		{
			*color = ft_color_add(*color,
					(t_color){._ = {.alpha = 0xff,
					.red = light->color._.red * n,
					.green = light->color._.green * n,
					.blue = light->color._.blue * n}});
		}
		tmp = tmp->next;
	}
}
