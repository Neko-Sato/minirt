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
# include "utils/vec3.h"

typedef struct s_cone
{
	t_abstract_figure	__parent;
}						t_cone;

typedef struct s_cone_init
{
	t_vec3				coord;
	float				diameter;
	t_vec3				apex;
	t_color				color;
	float				reflectivity;
	float				checker;
	void				*bump;
}						t_cone_init;

t_rt_errno				cone_init(\
	t_cone *self, t_cone_init *args);

void					cone_calculate_aabb(\
	t_cone *self);
int						cone_intersect(\
	t_cone *self, const t_ray *ray, float max_dist, float *dist);
t_vec3					cone_get_normal(\
	t_cone *self, const t_vec3 *point);
void					cone_get_uv_coord(\
	t_cone *self, const t_vec3 *point, float uv[2]);

#endif
