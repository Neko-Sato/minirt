/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   triangle.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 02:21:10 by hshimizu          #+#    #+#             */
/*   Updated: 2024/07/14 00:12:38 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TRIANGLE_H
# define TRIANGLE_H

# include "./abstract_figure.h"
# include "./texture.h"
# include "utils/vec3d.h"

typedef struct s_triangle
{
	t_abstract_figure	__parent;
	t_vec3d				a;
	t_vec3d				ab;
	t_vec3d				ac;
	t_vec3d				normal;
}						t_triangle;

typedef struct s_triangle_init
{
	t_vec3d				first;
	t_vec3d				second;
	t_vec3d				third;
	t_color				color;
	float				reflectivity;
	t_color				checker;
	void				*bump;
}						t_triangle_init;

t_rt_errno				triangle_init(\
	t_triangle *self, t_triangle_init *args);

void					triangle_calculate_aabb(\
	t_triangle *self);
int						triangle_intersect(\
	t_triangle *self, const t_ray *ray, float max_dist, float *dist);
t_ray					triangle_get_normal(\
	t_triangle *self, float dist, const t_ray *ray);

#endif
