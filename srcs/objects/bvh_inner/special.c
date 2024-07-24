/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 01:01:00 by hshimizu          #+#    #+#             */
/*   Updated: 2024/07/25 01:22:18 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects/abstract_figure.h"
#include "objects/bvh.h"
#include "objects/bvh_inner.h"
#include "utils/aabb.h"
#include "rt_errno.h"
#include <stdlib.h>

static const t_bvh_vtable	g_vtable = {
	.del = (void *)bvh_inner_del,
	.get_nearest = (void *)bvh_inner_get_nearest,
};

t_rt_errno	bvh_inner_init(t_bvh_inner *self, t_bvh_inner_init *args)
{
	t_bvh *const	bvh = (void *)self;

	*self = (t_bvh_inner){};
	self->left = args->left;
	self->right = args->right;
	bvh->_ = &g_vtable;
	bvh->aabb = aabb_merge(&args->left->aabb, &args->right->aabb);
	return (SUCCESS);
}

void	bvh_inner_del(t_bvh_inner *self)
{
	self->left->_->del(self->left);
	free(self->left);
	self->right->_->del(self->right);
	free(self->right);
}
