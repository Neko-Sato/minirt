/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bvh_inner.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 00:47:00 by hshimizu          #+#    #+#             */
/*   Updated: 2024/07/25 01:01:19 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BVH_INNER_H
# define BVH_INNER_H

# include "objects/bvh.h"
# include "objects/abstract_figure.h"
# include "rt_errno.h"

typedef struct s_bvh_inner
{
	t_bvh				__parent;
	t_bvh				*left;
	t_bvh				*right;
}						t_bvh_inner;

typedef struct s_bvh_inner_init
{
	t_bvh				*left;
	t_bvh				*right;
}						t_bvh_inner_init;

t_rt_errno				bvh_inner_init(\
	t_bvh_inner *self, t_bvh_inner_init *args);
void					bvh_inner_del(\
	t_bvh_inner *self);

t_abstract_figure		*bvh_inner_get_nearest(\
	t_bvh_inner *self, const t_ray *ray, float max_dist, float *dist);

#endif
