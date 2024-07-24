/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bvh_leaf.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 00:47:00 by hshimizu          #+#    #+#             */
/*   Updated: 2024/07/25 01:42:23 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BVH_LEAF_H
# define BVH_LEAF_H

# include "objects/bvh.h"
# include "rt_errno.h"

typedef struct s_bvh_leaf
{
	t_bvh				__parent;
	size_t				size;
	t_abstract_figure	**figures;
}						t_bvh_leaf;

typedef struct s_bvh_leaf_init
{
	t_abstract_figure	**figures;
	size_t				size;
}						t_bvh_leaf_init;

t_rt_errno				bvh_leaf_init(\
	t_bvh_leaf *self, t_bvh_leaf_init *args);
void					bvh_leaf_del(\
	t_bvh_leaf *self);

t_abstract_figure		*bvh_leaf_get_nearest(\
	t_bvh_leaf *self, const t_ray *ray, float max_dist, float *dist);

#endif
