/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   static_methods_0.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 01:25:23 by hshimizu          #+#    #+#             */
/*   Updated: 2024/07/26 04:17:47 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "constants.h"
#include "objects/abstract_figure.h"
#include "objects/bvh.h"

static void	figures_sort(t_abstract_figure **figures, size_t size, int axis)
{
	size_t				i;
	size_t				j;
	t_abstract_figure	*tmp;

	i = 0;
	while (i < size)
	{
		j = i + 1;
		while (j < size)
		{
			if (figures[i]->aabb.min._[axis] > figures[j]->aabb.min._[axis])
			{
				tmp = figures[i];
				figures[i] = figures[j];
				figures[j] = tmp;
			}
			j++;
		}
		i++;
	}
}

static float	get_cost(t_abstract_figure **figures, size_t size)
{
	t_aabb	aabb;
	size_t	i;

	i = 0;
	aabb = figures[i++]->aabb;
	while (i < size)
		aabb = aabb_merge(&aabb, &figures[i++]->aabb);
	return (aabb_surface_area(&aabb));
}

static inline void	find_best_split(t_abstract_figure **figures, size_t size,
		int *best_axis, float *best_point)
{
	int		axis;
	float	cost;
	float	best_cost;

	best_cost = INFINITY;
	axis = 0;
	while (axis < 3)
	{
		figures_sort(figures, size, axis);
		cost = get_cost(figures, size / 2);
		cost += get_cost(figures + (size / 2), size - (size / 2));
		if (axis == 0 || cost < best_cost)
		{
			*best_axis = axis;
			*best_point = figures[size / 2]->aabb.min._[axis];
			best_cost = cost;
		}
		axis++;
	}
}

size_t	bvh_figures_split(t_abstract_figure **figures, size_t size)
{
	int		axis;
	float	point;
	size_t	i;

	axis = 0;
	point = 0;
	find_best_split(figures, size, &axis, &point);
	figures_sort(figures, size, axis);
	i = 0;
	while (i < size && figures[i]->aabb.min._[axis] < point)
		i++;
	return (i);
}
