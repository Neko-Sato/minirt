/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   abstract_figure.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 02:16:57 by hshimizu          #+#    #+#             */
/*   Updated: 2024/07/12 18:12:52 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ABSTRACT_FIGURE_H
# define ABSTRACT_FIGURE_H

# include "utils/aabb.h"
# include "utils/ray.h"
# include "utils/vec3.h"
# include "utils/mat3x3.h"
# include "rt_errno.h"
# include <libft.h>

typedef struct s_abstract_figure_vtable	t_abstract_figure_vtable;

typedef struct s_abstract_figure
{
	const t_abstract_figure_vtable		*_;
	t_mat3x3							rotation;
	t_mat3x3							rotation_inv;
	t_vec3								position;
	t_aabb								aabb;
	t_color								color;
	t_color								checker;
	float								reflectivity;
	void								*bump;
}										t_abstract_figure;

typedef void							(*t_abstract_figure_del_fn)(
	t_abstract_figure *self);
typedef int								(*t_abstract_figure_intersect_fn)(
	t_abstract_figure *self, const t_ray *ray, float max_dist, float *dist);
typedef t_vec3							(*t_abstract_figure_get_normal_fn)(
	t_abstract_figure *self, const t_vec3 *point);
typedef void							(*t_abstract_figure_get_uv_coord_fn)(
	t_abstract_figure *self, const t_vec3 *point, float uv[2]);

typedef struct s_abstract_figure_vtable
{
	t_abstract_figure_del_fn			del;
	t_abstract_figure_intersect_fn		intersect;
	t_abstract_figure_get_normal_fn		get_normal;
	t_abstract_figure_get_uv_coord_fn	get_uv_coord;
}										t_abstract_figure_vtable;

typedef struct s_abstract_figure_init
{
	t_mat3x3							rotation;
	t_vec3								position;
	t_color								color;
	t_color								checker;
	float								reflectivity;
	void								*bump;
}										t_abstract_figure_init;

t_rt_errno								abstract_figure_init(\
	t_abstract_figure *self, t_abstract_figure_init *args);
void									abstract_figure_del(\
	t_abstract_figure *self);

t_color									abstract_figure_get_color(\
	t_abstract_figure *self, const t_vec3 *point);

#endif
