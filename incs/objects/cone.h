/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 02:26:08 by hshimizu          #+#    #+#             */
/*   Updated: 2024/07/14 00:12:02 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONE_H
# define CONE_H

# include "./abstract_figure.h"
# include "rt_errno.h"
# include "utils/ray.h"
# include "utils/vec3d.h"

typedef struct s_cone
{
	t_abstract_figure	__parent;
	t_vec3d				coord;
	float				radius;
	t_vec3d				axis;
	float				height;
}						t_cone;

typedef struct s_cone_init
{
	t_vec3d				coord;
	float				diameter;
	t_vec3d				apex;
	t_color				color;
	float				reflectivity;
	t_color				checker;
	void				*bump;
}						t_cone_init;

t_rt_errno				cone_init(\
	t_cone *self, t_cone_init *args);

void					cone_calculate_aabb(\
	t_cone *self);
int						cone_intersect(\
	t_cone *self, const t_ray *ray, float max_dist, float *dist);
t_ray					cone_get_normal(\
	t_cone *self, float dist, const t_ray *ray);

#endif
