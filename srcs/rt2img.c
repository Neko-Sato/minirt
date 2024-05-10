/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt2img.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 18:16:54 by hshimizu          #+#    #+#             */
/*   Updated: 2024/05/10 22:14:48 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <libft.h>
#include <math.h>

t_color	rt2img_internal(t_minirt *rt, t_vec3d o, t_vec3d c);

int	rt2img(t_minirt *rt, int size[2], unsigned int *img)
{
	int			i;
	t_vec3d		r;
	t_vec3d		u;
	long double	x;
	long double	y;

	r = vec3d_norm(vec3d_cross(rt->camera->orientation, (t_vec3d){{0, 1, 0}}));
	u = vec3d_norm(vec3d_cross(rt->camera->orientation, r));
	i = 0;
	while (i < size[0] * size[1])
	{
		x = (rt->camera->fov * M_PI / 180.l) * ((i % size[0]) - size[0] / 2.l)
			/ (double)size[0];
		y = (rt->camera->fov * M_PI / 180.l) * ((i / size[0]) - size[1] / 2.l)
			/ (double)size[0];
		img[i++] = rt2img_internal(rt,
				vec3d_norm(vec3d_add(vec3d_add(vec3d_mul(-tanl(x), r),
							vec3d_mul(tanl(y), u)), rt->camera->orientation)),
				rt->camera->coordinates).raw;
	}
	return (0);
}

t_color	rt2img_internal(t_minirt *rt, t_vec3d o, t_vec3d c)
{
	long double	k;
	long double	a;
	long double	b;

	(void)rt;
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
					return ((t_color){.raw = COLOR_RAW_BLUE});
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
	// 	return (0);
	// a = k * o._[0] + c._[0];
	// b = k * o._[2] + c._[2];
	// if (-0.5l <= a && a < 0.5l)
	// {
	// 	if (0 <= b)
	// 		return (0xff0000);
	// 	return (0x0000ff);
	// }
	// if (-0.5l <= b && b < 0.5l)
	// {
	// 	if (0 <= a)
	// 		return (0x00ff00);
	// 	return (0xff00ff);
	// }
	// if (fmodl(fmodl(a, 5) + 5, 5) < 1 || fmodl(fmodl(b, 5) + 5, 5) < 1)
	// 	return (0xffffff);
	// return (0);
}
