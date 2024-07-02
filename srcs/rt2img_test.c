/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt2img_test.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 00:17:41 by hshimizu          #+#    #+#             */
/*   Updated: 2024/07/02 01:05:59 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects/scene.h"
#include "utils/ray.h"
#include "utils/vec3d.h"
#include <libft.h>
#include <math.h>

t_color	rt2img_test1(const t_ray *r)
{
	float	k;
	float	a;
	float	b;

	k = -r->c._[1] / r->o._[1];
	if (k < 0)
		return ((t_color){.raw = COLOR_RAW_TRANSPARENT});
	a = k * r->o._[0] + r->c._[0];
	b = k * r->o._[2] + r->c._[2];
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

t_color	rt2img_test2(const t_ray *r)
{
	float	k;
	float	a;
	float	b;

	k = (50 - r->c._[2]) / r->o._[2];
	if (0 <= k)
	{
		a = k * r->o._[0] + r->c._[0];
		b = k * r->o._[1] + r->c._[1];
		if (fabsf(a) <= 50 && fabsf(b) <= 50)
		{
			if ((fmodf(fmodf(a, 5) + 5, 5) <= 0.5 || fmodf(fmodf(b, 5) + 5,
						5) <= 0.5))
				return ((t_color){.raw = COLOR_RAW_WHITE});
			else
				return ((t_color){.raw = COLOR_RAW_RED});
		}
	}
	k = (-50 - r->c._[2]) / r->o._[2];
	if (0 <= k)
	{
		a = k * r->o._[0] + r->c._[0];
		b = k * r->o._[1] + r->c._[1];
		if (fabsf(a) <= 50 && fabsf(b) <= 50)
		{
			if ((fmodf(fmodf(a, 5) + 5, 5) <= 0.5 || fmodf(fmodf(b, 5) + 5,
						5) <= 0.5))
				return ((t_color){.raw = COLOR_RAW_WHITE});
			else
				return ((t_color){.raw = COLOR_RAW_BLUE});
		}
	}
	k = (50 - r->c._[1]) / r->o._[1];
	if (0 <= k)
	{
		a = k * r->o._[0] + r->c._[0];
		b = k * r->o._[2] + r->c._[2];
		if (fabsf(a) <= 50 && fabsf(b) <= 50)
		{
			if ((fmodf(fmodf(a, 5) + 5, 5) <= 0.5l || fmodf(fmodf(b, 5) + 5,
						5) <= 0.5l))
				return ((t_color){.raw = COLOR_RAW_WHITE});
			else
				return ((t_color){.raw = COLOR_RAW_GREEN});
		}
	}
	k = (-50 - r->c._[1]) / r->o._[1];
	if (0 <= k)
	{
		a = k * r->o._[0] + r->c._[0];
		b = k * r->o._[2] + r->c._[2];
		if (fabsf(a) <= 50 && fabsf(b) <= 50)
		{
			if ((fmodf(fmodf(a, 5) + 5, 5) <= 0.5l || fmodf(fmodf(b, 5) + 5,
						5) <= 0.5l))
				return ((t_color){.raw = COLOR_RAW_WHITE});
			else
				return ((t_color){.raw = COLOR_RAW_MAGENTA});
		}
	}
	k = (50 - r->c._[0]) / r->o._[0];
	if (0 <= k)
	{
		a = k * r->o._[1] + r->c._[1];
		b = k * r->o._[2] + r->c._[2];
		if (fabsf(a) <= 50 && fabsf(b) <= 50)
		{
			if ((fmodf(fmodf(a, 5) + 5, 5) <= 0.5l || fmodf(fmodf(b, 5) + 5,
						5) <= 0.5l))
				return ((t_color){.raw = COLOR_RAW_WHITE});
			else
				return ((t_color){.raw = COLOR_RAW_YELLOW});
		}
	}
	k = (-50 - r->c._[0]) / r->o._[0];
	if (0 <= k)
	{
		a = k * r->o._[1] + r->c._[1];
		b = k * r->o._[2] + r->c._[2];
		if (fabsf(a) <= 50 && fabsf(b) <= 50)
		{
			if ((fmodf(fmodf(a, 5) + 5, 5) <= 0.5l || fmodf(fmodf(b, 5) + 5,
						5) <= 0.5l))
				return ((t_color){.raw = COLOR_RAW_WHITE});
			else
				return ((t_color){.raw = COLOR_RAW_CYAN});
		}
	}
	return ((t_color){.raw = COLOR_RAW_BLACK});
}
