/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 02:21:10 by hshimizu          #+#    #+#             */
/*   Updated: 2024/07/05 18:39:58 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PLANE_H
# define PLANE_H

# include "./figure.h"
# include "utils/vec3d.h"

typedef struct s_plane
{
	t_figure		__parent;
	t_vec3d			coord;
	t_vec3d			orient;
}					t_plane;

typedef struct s_plane_init
{
	t_vec3d			coord;
	t_vec3d			orient;
	t_color			color;
	t_figure_opt	opt;
}					t_plane_init;

t_rt_errno			plane_init(t_plane *self, t_plane_init *args);
void				plane_del(t_plane *self);

void				plane_set_aabb(t_plane *self);
int					plane_intersect(t_plane *self, const t_ray *r,
						float max_dist, float *t);
t_ray				plane_get_normal(t_plane *self, float dist, const t_ray *r);

#endif
