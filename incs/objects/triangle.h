/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   triangle.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 02:21:10 by hshimizu          #+#    #+#             */
/*   Updated: 2024/08/01 22:37:15 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TRIANGLE_H
# define TRIANGLE_H

# include "./abstract_figure.h"
# include "utils/vec3.h"

typedef struct s_triangle
{
	t_abstract_figure	__parent;
}						t_triangle;

typedef struct s_triangle_init
{
	t_vec3				first;
	t_vec3				second;
	t_vec3				third;
	t_color				color;
	float				reflectivity;
	float				checker;
	void				*bump;
}						t_triangle_init;

t_rt_errno				triangle_init(\
	t_triangle *self, t_triangle_init *args);

void					triangle_calculate_aabb(\
	t_triangle *self);
int						triangle_intersect(\
	t_triangle *self, const t_ray *ray, float max_dist, float *dist);
t_vec3					triangle_get_normal(\
	t_triangle *self, const t_vec3 *point);
void					triangle_get_uv_coord(\
	t_triangle *self, const t_vec3 *point, float uv[2]);

#endif
