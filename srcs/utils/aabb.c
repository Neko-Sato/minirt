/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aabb.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 10:04:50 by hshimizu          #+#    #+#             */
/*   Updated: 2024/07/13 10:22:16 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils/aabb.h"
#include "utils/ray.h"
#include "utils/vec3d.h"
#include "constants.h"

int	aabb_contains(const t_aabb *aabb, const t_ray *ray, float max_dist)
{
	float	min_dist;
	float	tmp[2];
	int		i;

	min_dist = MIN_DIST;
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
		else if (ray->c._[i] < aabb->min._[i]
			|| ray->c._[i] > aabb->max._[i])
			return (0);
		i++;
	}
	return (1);
}
