/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   methods_0.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 01:07:33 by hshimizu          #+#    #+#             */
/*   Updated: 2024/07/25 01:47:33 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects/abstract_figure.h"
#include "objects/bvh.h"
#include "objects/bvh_leaf.h"
#include "utils/aabb.h"

t_abstract_figure	*bvh_leaf_get_nearest(t_bvh_leaf *self, const t_ray *ray,
		float max_dist, float *dist)
{
	t_bvh *const		bvh = (void *)self;
	t_abstract_figure	*figure;
	t_abstract_figure	*nearest;
	float				t;
	size_t				i;

	if (!aabb_contains(&bvh->aabb, ray, max_dist))
		return (NULL);
	nearest = NULL;
	i = 0;
	while (i < self->size)
	{
		figure = self->figures[i++];
		if (!figure->_->intersect(figure, ray, max_dist, &t))
			continue ;
		nearest = figure;
		max_dist = t;
	}
	if (nearest)
		*dist = t;
	return (nearest);
}
