/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aabb.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 10:04:50 by hshimizu          #+#    #+#             */
/*   Updated: 2024/07/24 23:50:17 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils/aabb.h"
#include "utils/mat3x3.h"
#include "utils/ray.h"
#include "utils/vec3.h"
#include <math.h>

int	aabb_contains(const t_aabb *aabb, const t_ray *ray, float max_dist)
{
	float	min_dist;
	float	tmp[2];
	int		i;

	min_dist = 0;
	i = 0;
	while (i < 3)
	{
		if (ray->o._[i])
		{
			tmp[0] = (aabb->min._[i] - ray->c._[i]) / ray->o._[i];
			tmp[1] = (aabb->max._[i] - ray->c._[i]) / ray->o._[i];
			min_dist = fmax(min_dist, fmin(tmp[0], tmp[1]));
			max_dist = fmin(max_dist, fmax(tmp[0], tmp[1]));
			if (min_dist > max_dist)
				return (0);
		}
		else if (ray->c._[i] < aabb->min._[i] || ray->c._[i] > aabb->max._[i])
			return (0);
		i++;
	}
	return (1);
}

t_aabb	aabb_merge(const t_aabb *a, const t_aabb *b)
{
	t_aabb	res;
	int		i;

	i = 0;
	while (i < 3)
	{
		res.min._[i] = fmin(a->min._[i], b->min._[i]);
		res.max._[i] = fmax(a->max._[i], b->max._[i]);
		i++;
	}
	return (res);
}

void	aabb_expand(t_aabb *aabb, const t_vec3 *point)
{
	int	i;

	i = 0;
	while (i < 3)
	{
		aabb->min._[i] = fmin(aabb->min._[i], point->_[i]);
		aabb->max._[i] = fmax(aabb->max._[i], point->_[i]);
		i++;
	}
}

t_aabb	aabb_transform(const t_aabb *aabb, const t_mat3x3 *rotation,
		const t_vec3 *position)
{
	t_aabb	res;
	t_vec3	tmp;
	int		i;
	int		j;

	i = 0;
	while (i < 8)
	{
		j = 0;
		while (j < 3)
		{
			if (i & (1 << j))
				tmp._[j] = aabb->max._[j];
			else
				tmp._[j] = aabb->min._[j];
			j++;
		}
		tmp = vec3_add(mat3x3_mul_vec3(*rotation, tmp), *position);
		if (!i)
			res = (t_aabb){tmp, tmp};
		else
			aabb_expand(&res, &tmp);
		i++;
	}
	return (res);
}

float	aabb_surface_area(const t_aabb *aabb)
{
	const float	dx = aabb->max._[0] - aabb->min._[0];
	const float	dy = aabb->max._[1] - aabb->min._[1];
	const float	dz = aabb->max._[2] - aabb->min._[2];

	return (2 * (dx * dy + dx * dz + dy * dz));
}
