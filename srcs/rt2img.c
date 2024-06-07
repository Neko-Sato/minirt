/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt2img.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 00:17:41 by hshimizu          #+#    #+#             */
/*   Updated: 2024/06/08 00:36:12 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects/scene.h"
#include "rt_errno.h"
#include "utils/ray.h"
#include "utils/vec3d.h"
#include <libft.h>
#include <math.h>

t_color	rt2img_internal(t_scene *scene, t_ray r);

int	rt2img(t_scene *scene, unsigned int *img)
{
	const t_vec3d		f = vec3d_norm(scene->camera->orientation);
	const t_vec3d		r = vec3d_norm(vec3d_cross((t_vec3d){{0, 1, 0}}, f));
	const t_vec3d		u = vec3d_norm(vec3d_cross(f, r));
	const long double	d = ft_deg2rad(scene->camera->fov
			/ (long double)scene->camera->width);
	int					i;
	int					j;

	i = -scene->camera->height / 2;
	while (i < scene->camera->height / 2)
	{
		j = -scene->camera->width / 2;
		while (j < scene->camera->width / 2)
		{
			*img++ = rt2img_internal(scene, (t_ray){
					.o = vec3d_add(vec3d_add(
							vec3d_mul(tanl(d * j), r),
							vec3d_mul(-tanl(d * i), u)),
						f),
					.c = scene->camera->coordinates}).raw;
			j++;
		}
		i++;
	}
	return (NO_ERROR);
}

t_color	rt2img_internal(t_scene *scene, t_ray r)
{	
	t_vec3d o = r.o, c = r.c;
	long double	k;
	long double	a;
	long double	b;

	(void)scene;
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
	return ((t_color){.raw = COLOR_RAW_BLACK});

	k = -c._[1] / o._[1];
	if (k < 0)
		return ((t_color){.raw = COLOR_RAW_TRANSPARENT});
	a = k * o._[0] + c._[0];
	b = k * o._[2] + c._[2];
	if (-0.5l <= a && a < 0.5l)
	{
		if (0 <= b)
			return ((t_color){.raw = COLOR_RAW_RED});
		return ((t_color){.raw = COLOR_RAW_BLUE});
	}
	if (-0.5l <= b && b < 0.5l)
	{
		if (0 <= a)
			return ((t_color){.raw = COLOR_RAW_GREEN});
		return ((t_color){.raw = COLOR_RAW_MAGENTA});
	}
	if (fmodl(fmodl(a, 5) + 5, 5) < 1 || fmodl(fmodl(b, 5) + 5, 5) < 1)
		return ((t_color){.raw = COLOR_RAW_WHITE});
	return ((t_color){.raw = COLOR_RAW_TRANSPARENT});
}
