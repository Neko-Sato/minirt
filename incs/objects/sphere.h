/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 02:21:10 by hshimizu          #+#    #+#             */
/*   Updated: 2024/07/05 18:14:28 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SPHERE_H
# define SPHERE_H

# include "./figure.h"

typedef struct s_sphere
{
	t_figure		__parent;
	t_vec3d			coord;
	float			radius;
}					t_sphere;

typedef struct s_sphere_init
{
	t_vec3d			coord;
	float			diameter;
	t_color			color;
	t_figure_opt	opt;
}					t_sphere_init;

t_rt_errno			sphere_init(t_sphere *self, t_sphere_init *args);
void				sphere_del(t_sphere *self);

void				sphere_set_aabb(t_sphere *self);
int					sphere_intersect(t_sphere *self, const t_ray *r,
						float max_dist, float *t);
t_ray				sphere_get_normal(t_sphere *self, float dist,
						const t_ray *r);

#endif
