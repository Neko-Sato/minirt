/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 02:26:08 by hshimizu          #+#    #+#             */
/*   Updated: 2024/07/05 18:39:34 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CYLINDER_H
# define CYLINDER_H

# include "./figure.h"
# include "rt_errno.h"
# include "utils/matrix3x3.h"
# include "utils/vec3d.h"

typedef struct s_cylinder
{
	t_figure		__parent;
	t_vec3d			coord;
	t_vec3d			axis;
	float			radius;
	float			height;
}					t_cylinder;

typedef struct s_cylinder_init
{
	t_vec3d			coord;
	t_vec3d			axis;
	float			diameter;
	float			height;
	t_color			color;
	t_figure_opt	opt;
}					t_cylinder_init;

t_rt_errno			cylinder_init(t_cylinder *self, t_cylinder_init *args);
void				cylinder_del(t_cylinder *self);

void				cylinder_set_aabb(t_cylinder *self);
int					cylinder_intersect(t_cylinder *self, const t_ray *r,
						float max_dist, float *t);
t_ray				cylinder_get_normal(t_cylinder *self, float dist,
						const t_ray *r);

#endif
