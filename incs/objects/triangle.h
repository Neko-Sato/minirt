/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   triangle.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 02:21:10 by hshimizu          #+#    #+#             */
/*   Updated: 2024/06/29 01:17:32 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TRIANGLE_H
# define TRIANGLE_H

# include "./figure.h"
# include "utils/vec3d.h"

typedef struct s_triangle
{
	t_figure		__parent;
	t_vec3d			first;
	t_vec3d			second;
	t_vec3d			third;
}					t_triangle;

typedef struct s_triangle_init
{
	t_vec3d			first;
	t_vec3d			second;
	t_vec3d			third;
	t_color			color;
	t_figure_opt	opt;
}					t_triangle_init;

t_rt_errno			triangle_init(t_triangle *self, t_triangle_init *args);
void				triangle_del(t_triangle *self);

void				triangle_set_aabb(t_triangle *self);
int					triangle_intersect(t_triangle *self, const t_ray *r,
						float max_dist, float *t);

#endif
