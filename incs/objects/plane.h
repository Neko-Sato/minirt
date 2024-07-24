/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 02:21:10 by hshimizu          #+#    #+#             */
/*   Updated: 2024/07/24 04:27:42 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PLANE_H
# define PLANE_H

# include "./abstract_figure.h"
# include "utils/vec3.h"

typedef struct s_plane
{
	t_abstract_figure	__parent;
}						t_plane;

typedef struct s_plane_init
{
	t_vec3				coord;
	t_vec3				orient;
	t_color				color;
	float				reflectivity;
	t_color				checker;
	void				*bump;
}						t_plane_init;

t_rt_errno				plane_init(\
	t_plane *self, t_plane_init *args);

void					plane_calculate_aabb(\
	t_plane *self);
int						plane_intersect(\
	t_plane *self, const t_ray *ray, float max_dist, float *dist);
t_vec3					plane_get_normal(\
	t_plane *self, const t_vec3 *point);
void					plane_get_uv_coord(\
	t_plane *self, const t_vec3 *point, float uv[2]);

#endif
