/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   methods_0.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 01:07:33 by hshimizu          #+#    #+#             */
/*   Updated: 2024/07/25 01:43:20 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects/abstract_figure.h"
#include "objects/bvh.h"
#include "objects/bvh_inner.h"
#include "utils/aabb.h"

t_abstract_figure	*bvh_inner_get_nearest(t_bvh_inner *self, const t_ray *ray,
		float max_dist, float *dist)
{
	t_bvh *const		bvh = (void *)self;
	t_abstract_figure	*figure;
	t_abstract_figure	*nearest;
	float				t;

	if (!aabb_contains(&bvh->aabb, ray, max_dist))
		return (NULL);
	nearest = NULL;
	figure = self->left->_->get_nearest(self->left, ray, max_dist, &t);
	if (figure)
	{
		nearest = figure;
		max_dist = t;
	}
	figure = self->right->_->get_nearest(self->right, ray, max_dist, &t);
	if (figure)
	{
		nearest = figure;
		max_dist = t;
	}
	if (nearest)
		*dist = t;
	return (nearest);
}
