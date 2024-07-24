/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 01:01:00 by hshimizu          #+#    #+#             */
/*   Updated: 2024/07/25 01:21:26 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects/abstract_figure.h"
#include "objects/bvh.h"
#include "objects/bvh_leaf.h"
#include "utils/aabb.h"
#include "rt_errno.h"
#include <stdlib.h>

static const t_bvh_vtable	g_vtable = {
	.del = (void *)bvh_leaf_del,
	.get_nearest = (void *)bvh_leaf_get_nearest,
};

t_rt_errno	bvh_leaf_init(t_bvh_leaf *self, t_bvh_leaf_init *args)
{
	t_bvh *const	bvh = (void *)self;
	size_t			i;

	*self = (t_bvh_leaf){};
	self->size = args->size;
	self->figures = args->figures;
	bvh->_ = &g_vtable;
	if (self->size)
	{
		i = 0;
		bvh->aabb = self->figures[i++]->aabb;
		while (i < self->size)
			bvh->aabb = aabb_merge(&bvh->aabb, &args->figures[i++]->aabb);
	}
	return (SUCCESS);
}

void	bvh_leaf_del(t_bvh_leaf *self)
{
	(void)self;
}
