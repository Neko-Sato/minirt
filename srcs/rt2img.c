/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt2img.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 00:17:41 by hshimizu          #+#    #+#             */
/*   Updated: 2024/06/05 00:21:18 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects/scene.h"
#include "utils/vec3d.h"
#include <libft.h>
#include <math.h>

t_color	rt2img_internal(t_scene *scene, t_vec3d o, t_vec3d c);

int	rt2img(t_scene *scene, unsigned int *img, int width, int height)
{
	int			i;
	t_vec3d		r;
	t_vec3d		u;
	long double	x;
	long double	y;

	r = vec3d_norm(vec3d_cross(scene->camera->orientation, (t_vec3d){{0, 1,
				0}}));
	u = vec3d_norm(vec3d_cross(scene->camera->orientation, r));
	i = 0;
	while (i < width * height)
	{
		x = (scene->camera->fov * M_PI / 180.l) * ((i % width) - width
				/ 2.l) / (double)width;
		y = (scene->camera->fov * M_PI / 180.l) * ((i / width) - height
				/ 2.l) / (double)width;
		img[i++] = rt2img_internal(scene,
				vec3d_norm(vec3d_add(vec3d_add(vec3d_mul(-tanl(x), r),
							vec3d_mul(tanl(y), u)),
						scene->camera->orientation)),
				scene->camera->coordinates).raw;
	}
	return (0);
}

t_color	rt2img_internal(t_scene *scene, t_vec3d o, t_vec3d c)
{
	long double	k;
	long double	a;
	long double	b;

	(void)scene;
	k = (10 - c._[2]) / o._[2];
	if (fabsl(k * o._[0] + c._[0]) < 5 && fabsl(k * o._[1] + c._[1]) < 5)
		return ((t_color){.raw = COLOR_RAW_BLACK});
	//前後
	{
		k = (50 - c._[2]) / o._[2];
		if (0 <= k)
		{
			a = k * o._[0] + c._[0];
			b = k * o._[1] + c._[1];
			if (fabsl(a) <= 50 && fabsl(b) <= 50)
			{
				if ((fmodl(fmodl(a, 5) + 5, 5) <= 0.5l || fmodl(fmodl(b, 5) + 5,
							5) <= 0.5l))
					return ((t_color){.raw = COLOR_RAW_WHITE});
				else
					return ((t_color){.raw = COLOR_RAW_RED});
			}
		}
		k = (-50 - c._[2]) / o._[2];
		if (0 <= k)
		{
			a = k * o._[0] + c._[0];
			b = k * o._[1] + c._[1];
			if (fabsl(a) <= 50 && fabsl(b) <= 50)
			{
				if ((fmodl(fmodl(a, 5) + 5, 5) <= 0.5l || fmodl(fmodl(b, 5) + 5,
							5) <= 0.5l))
					return ((t_color){.raw = COLOR_RAW_WHITE});
				else
					return ((t_color){.raw = COLOR_RAW_BLUE});
			}
		}
	}
	//上下
	{
		k = (50 - c._[1]) / o._[1];
		if (0 <= k)
		{
			a = k * o._[0] + c._[0];
			b = k * o._[2] + c._[2];
			if (fabsl(a) <= 50 && fabsl(b) <= 50)
			{
				if ((fmodl(fmodl(a, 5) + 5, 5) <= 0.5l || fmodl(fmodl(b, 5) + 5,
							5) <= 0.5l))
					return ((t_color){.raw = COLOR_RAW_WHITE});
				else
					return ((t_color){.raw = COLOR_RAW_GREEN});
			}
		}
		k = (-50 - c._[1]) / o._[1];
		if (0 <= k)
		{
			a = k * o._[0] + c._[0];
			b = k * o._[2] + c._[2];
			if (fabsl(a) <= 50 && fabsl(b) <= 50)
			{
				if ((fmodl(fmodl(a, 5) + 5, 5) <= 0.5l || fmodl(fmodl(b, 5) + 5,
							5) <= 0.5l))
					return ((t_color){.raw = COLOR_RAW_WHITE});
				else
					return ((t_color){.raw = COLOR_RAW_MAGENTA});
			}
		}
	}
	//左右
	{
		k = (50 - c._[0]) / o._[0];
		if (0 <= k)
		{
			a = k * o._[1] + c._[1];
			b = k * o._[2] + c._[2];
			if (fabsl(a) <= 50 && fabsl(b) <= 50)
			{
				if ((fmodl(fmodl(a, 5) + 5, 5) <= 0.5l || fmodl(fmodl(b, 5) + 5,
							5) <= 0.5l))
					return ((t_color){.raw = COLOR_RAW_WHITE});
				else
					return ((t_color){.raw = COLOR_RAW_YELLOW});
			}
		}
		k = (-50 - c._[0]) / o._[0];
		if (0 <= k)
		{
			a = k * o._[1] + c._[1];
			b = k * o._[2] + c._[2];
			if (fabsl(a) <= 50 && fabsl(b) <= 50)
			{
				if ((fmodl(fmodl(a, 5) + 5, 5) <= 0.5l || fmodl(fmodl(b, 5) + 5,
							5) <= 0.5l))
					return ((t_color){.raw = COLOR_RAW_WHITE});
				else
					return ((t_color){.raw = COLOR_RAW_CYAN});
			}
		}
	}
	return ((t_color){.raw = COLOR_RAW_TRANSPARENT});
	// k = -c._[1] / o._[1];
	// if (k < 0)
	// 	return ((t_color){.raw = COLOR_RAW_TRANSPARENT});
	// a = k * o._[0] + c._[0];
	// b = k * o._[2] + c._[2];
	// if (-0.5l <= a && a < 0.5l)
	// {
	// 	if (0 <= b)
	// 		return ((t_color){.raw = COLOR_RAW_RED});
	// 	return ((t_color){.raw = COLOR_RAW_BLUE});
	// }
	// if (-0.5l <= b && b < 0.5l)
	// {
	// 	if (0 <= a)
	// 		return ((t_color){.raw = COLOR_RAW_GREEN});
	// 	return ((t_color){.raw = COLOR_RAW_MAGENTA});
	// }
	// if (fmodl(fmodl(a, 5) + 5, 5) < 1 || fmodl(fmodl(b, 5) + 5, 5) < 1)
	// 	return ((t_color){.raw = COLOR_RAW_WHITE});
	// return ((t_color){.raw = COLOR_RAW_TRANSPARENT});
}