/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt2img.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 03:07:02 by hshimizu          #+#    #+#             */
/*   Updated: 2024/06/22 01:30:54 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects/scene.h"
#include "rt2img.h"
#include "utils/ray.h"
#include "utils/vec3d.h"
#include <libft.h>
#include <math.h>

#define PIXEL_SIZE 10000.0

/*
	今はとりあえず適当に書こうか、、、
*/

//    最も近いオブジェクトと、その交点を取得 (__)
//    その座標においての色を得る (__)
//    反射率が0超過ならば法線ベクトルを導き、再帰的に取得し、(__)
//    反射率を考慮し、得た値に適応させる(__)
//    オブジェクトがなければ黒　(OK)
//    そこにamibientsを適応させる　(OK)
//    そこに”前方にある”全ての光源を距離の逆二乗し適応させる。　(OK)

// t_figure	*get_nearest(t_rtobjs *objs, t_ray *r, t_vec3d *intersection);
// t_color		get_color(t_figure	*figure, t_vec3d *intersection);

static inline t_color	color_ambients(t_xlst *ambients);
static inline t_color	color_lights(t_xlst *lights, t_ray *r);

t_color	rt2img(t_rtobjs *objs, t_ray *r, int max_depth)
{
	t_color	color;

	// t_figure	*nearest;
	// t_vec3d		intersection;
	(void)objs;
	color = (t_color){.raw = COLOR_RAW_BLACK};
	if (max_depth <= 0)
		return (color);
	color = rt2img_test1(r);
	// nearest = get_nearest(objs, r, &intersection);
	// if (!nearest)
	// {
	// 	// color = get_color(figure, objs, r, &intersection);
	// 	// if (0. < nearest->reflectivity)
	// 	// 	color = color_add(color, rt2img(objs, &reflected_ray, max_depth
	// - 1));
	// }
	return (ft_color_add(ft_color_sub(color, color_ambients(objs->ambients)),
			color_lights(objs->lights, r)));
}

/*
	光の強さ(彩度)いじるとき用の関数があった方がいい気がする
*/

static inline t_color	color_ambients(t_xlst *ambients)
{
	t_xlst		*tmp;
	t_ambient	*ambient;
	t_color		c[2];

	c[0].raw = COLOR_RAW_BLACK;
	tmp = ambients;
	while (tmp)
	{
		ambient = *(t_ambient **)tmp->data;
		c[1]._.alpha = ambient->color._.alpha;
		c[1]._.red = ambient->color._.red * ambient->ratio;
		c[1]._.blue = ambient->color._.blue * ambient->ratio;
		c[1]._.green = ambient->color._.green * ambient->ratio;
		c[0] = ft_color_add(c[0], c[1]);
		tmp = tmp->next;
	}
	return (c[0]);
}

static inline t_color	color_lights(t_xlst *lights, t_ray *r)
{
	t_xlst	*tmp;
	t_light	*light;
	t_color	c[2];
	t_vec3d	vec;
	float	var;

	c[0].raw = COLOR_RAW_BLACK;
	tmp = lights;
	while (tmp)
	{
		light = *(t_light **)tmp->data;
		vec = vec3d_sub(light->coordinates, r->c);//間にオブジェクトがあったらダメ
		var = vec3d_dot(vec, r->o) / (vec3d_abs(vec) * vec3d_abs(r->o));
		if (0. <= var)
		{
			var *= light->brightness / pow(1 + vec3d_abs(vec) / PIXEL_SIZE, 2);
			c[1]._.alpha = light->color._.alpha;
			c[1]._.red = light->color._.red * var;
			c[1]._.blue = light->color._.blue * var;
			c[1]._.green = light->color._.green * var;
			c[0] = ft_color_add(c[0], c[1]);
		}
		tmp = tmp->next;
	}
	return (c[0]);
}
