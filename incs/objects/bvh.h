/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bvh.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 00:47:00 by hshimizu          #+#    #+#             */
/*   Updated: 2024/07/25 01:41:48 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BVH_H
# define BVH_H

# include "objects/abstract_figure.h"
# include "rt_errno.h"

typedef struct s_bvh_vtable	t_bvh_vtable;

typedef struct s_bvh
{
	const t_bvh_vtable		*_;
	t_aabb					aabb;
}							t_bvh;

typedef void				(*t_bvh_del_fn)(\
	t_bvh *self);
typedef t_abstract_figure	*(*t_bvh_get_nearest_fn)(\
	t_bvh *self, const t_ray *ray, float max_dist, float *dist);

typedef struct s_bvh_vtable
{
	t_bvh_del_fn			del;
	t_bvh_get_nearest_fn	get_nearest;
}							t_bvh_vtable;

typedef struct s_bvh_init
{
	t_aabb					aabb;
}							t_bvh_init;

size_t						bvh_figures_split(\
	t_abstract_figure **figures,
								size_t size);

typedef struct s_bvh_task
{
	t_bvh					*left;
	t_bvh					*right;
	size_t					start;
	size_t					size;
	size_t					split;
}							t_bvh_task;

typedef struct s_bvh_build_local
{
	t_abstract_figure		**figures;
	size_t					size;
	t_stack					*stack;
	t_bvh_task				task;
	t_bvh					*tmp;
}							t_bvh_build_local;

t_rt_errno					bvh_build(\
	t_bvh **bvh, t_abstract_figure **figures, size_t size);

#endif
