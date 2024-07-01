/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt2img.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 03:07:02 by hshimizu          #+#    #+#             */
/*   Updated: 2024/06/29 14:26:45 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects/scene.h"
#include "rt2img.h"
#include "utils/ray.h"
#include "utils/vec3d.h"
#include <libft.h>
#include <math.h>

// #define PIXEL_SIZE 10000.0

/*
	いずれsceneオブジェクトのメソッドにします。
	traceメソッド
*/

//	最も近いオブジェクトとその距離を取得
//	オブジェクトがあれば
//		その色を得る
//		環境光ambientの適応
//		法線ベクトルを取得
//		法線ベクトルに対して(光源)拡散反射の適応
//		反射率が0超過ならば法線ベクトルを導き、再帰的に取得し、(__)
//    反射率を考慮し、得た値に適応させる(__)
//  オブジェクトがなければ黒　(OK)
//  光源　(OK)

// t_color		get_color(t_figure	*figure, t_vec3d *intersection);

// static inline t_color	color_ambients(t_xlst *ambients);
// static inline t_color	color_lights(t_xlst *lights, t_xlst *figures, t_ray *r);

t_figure	*get_nearest(t_scene *scene, t_ray *r, float max_dist, float *dist)
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

t_color	rt2img(t_scene *scene, t_ray *r, float max_dist, int max_depth)
{
	t_color		color;
	t_figure	*nearest;
	float		dist;
	t_vec3d		point;

	color.raw = 0;
	if (!max_depth)
		return (color);
	nearest = get_nearest(scene, r, max_dist, &dist);
	if (nearest)
	{
		point = vec3d_add(vec3d_mul(dist, r->o), r->c);
		color = nearest->_->get_color(nearest, &point);
	}
	// else
	// 	color = rt2img_test1(r);
	return (color);
}

// static inline t_color	color_ambients(t_xlst *ambients)
// {
// 	t_xlst		*tmp;
// 	t_ambient	*ambient;
// 	t_color		c;

// 	c.raw = COLOR_RAW_BLACK;
// 	tmp = ambients;
// 	while (tmp)
// 	{
// 		ambient = *(t_ambient **)tmp->data;
// 		c = ft_color_add(c, adjust_brightness(ambient->color, ambient->ratio));
// 		tmp = tmp->next;
// 	}
// 	return (c);
// }

// static inline t_color	color_lights(t_xlst *lights, t_xlst *figures, t_ray *r)
// {
// 	t_xlst	*tmp;
// 	t_light	*light;
// 	t_color	c;
// 	t_vec3d	vec;
// 	float	var;

// 	c.raw = COLOR_RAW_BLACK;
// 	tmp = lights;
// 	while (tmp)
// 	{
// 		light = *(t_light **)tmp->data;
// 		vec = vec3d_sub(light->coordinates, r->c);
// 		if (1 /*!get_nearest(figures, r, NULL)*/)
// 		{
// 			var = vec3d_dot(vec, r->o) / (vec3d_abs(vec) * vec3d_abs(r->o));
// 			if (0. <= var)
// 			{
// 				var *= light->brightness / pow(1 + vec3d_abs(vec) / PIXEL_SIZE,
// 						2);
// 				c = ft_color_add(c, adjust_brightness(light->color, var));
// 			}
// 		}
// 		tmp = tmp->next;
// 	}
// 	return (c);
// }
