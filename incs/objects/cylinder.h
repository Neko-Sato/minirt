/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 02:26:08 by hshimizu          #+#    #+#             */
/*   Updated: 2024/07/20 04:25:39 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CYLINDER_H
# define CYLINDER_H

# include "./abstract_figure.h"
# include "rt_errno.h"
# include "utils/ray.h"
# include "utils/vec3d.h"

typedef struct s_cylinder
{
	t_abstract_figure	__parent;
	t_vec3d				coord;
	t_vec3d				axis;
	float				radius;
	float				height;
}						t_cylinder;

typedef struct s_cylinder_init
{
	t_vec3d				coord;
	t_vec3d				axis;
	float				diameter;
	float				height;
	t_color				color;
	float				reflectivity;
	t_color				checker;
	void				*bump;
}						t_cylinder_init;

t_rt_errno				cylinder_init(\
	t_cylinder *self, t_cylinder_init *args);

void					cylinder_calculate_aabb(\
	t_cylinder *self);
int						cylinder_intersect(\
	t_cylinder *self, const t_ray *ray, float max_dist, float *dist);
t_ray					cylinder_get_normal(\
	t_cylinder *self, float dist, const t_ray *ray);
void					cylinder_get_uv_coord(\
	t_cylinder *self, const t_vec3d *point, float uv[2]);

#endif
