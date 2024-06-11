/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt2img.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 00:17:41 by hshimizu          #+#    #+#             */
/*   Updated: 2024/06/12 02:43:45 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects/scene.h"
#include "utils/ray.h"
#include "utils/vec3d.h"
#include <libft.h>
#include <math.h>

t_color	rt2img(t_rtobjs *objs, t_ray *r)
{
	float	k;
	float	a;
	float	b;

	t_vec3d o, c;
	o = r->o;
	c = r->c;
	(void)objs;
	//前後
	{
		k = (50 - c._[2]) / o._[2];
		if (0 <= k)
		{
			a = k * o._[0] + c._[0];
			b = k * o._[1] + c._[1];
			if (fabsf(a) <= 50 && fabsf(b) <= 50)
			{
				if ((fmodf(fmodf(a, 5) + 5, 5) <= 0.5 || fmodf(fmodf(b, 5) + 5,
							5) <= 0.5))
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
			if (fabsf(a) <= 50 && fabsf(b) <= 50)
			{
				if ((fmodf(fmodf(a, 5) + 5, 5) <= 0.5 || fmodf(fmodf(b, 5) + 5,
							5) <= 0.5))
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
			if (fabsf(a) <= 50 && fabsf(b) <= 50)
			{
				if ((fmodf(fmodf(a, 5) + 5, 5) <= 0.5l || fmodf(fmodf(b, 5) + 5,
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
			if (fabsf(a) <= 50 && fabsf(b) <= 50)
			{
				if ((fmodf(fmodf(a, 5) + 5, 5) <= 0.5l || fmodf(fmodf(b, 5) + 5,
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
			if (fabsf(a) <= 50 && fabsf(b) <= 50)
			{
				if ((fmodf(fmodf(a, 5) + 5, 5) <= 0.5l || fmodf(fmodf(b, 5) + 5,
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
			if (fabsf(a) <= 50 && fabsf(b) <= 50)
			{
				if ((fmodf(fmodf(a, 5) + 5, 5) <= 0.5l || fmodf(fmodf(b, 5) + 5,
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
	if (-0.5f <= a && a < 0.5f)
	{
		if (0 <= b)
			return ((t_color){.raw = COLOR_RAW_RED});
		return ((t_color){.raw = COLOR_RAW_BLUE});
	}
	if (-0.5f <= b && b < 0.5f)
	{
		if (0 <= a)
			return ((t_color){.raw = COLOR_RAW_GREEN});
		return ((t_color){.raw = COLOR_RAW_MAGENTA});
	}
	if (fmodf(fmodf(a, 5) + 5, 5) < 1 || fmodf(fmodf(b, 5) + 5, 5) < 1)
		return ((t_color){.raw = COLOR_RAW_WHITE});
	return ((t_color){.raw = COLOR_RAW_TRANSPARENT});
}
