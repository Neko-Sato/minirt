/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 22:50:33 by hshimizu          #+#    #+#             */
/*   Updated: 2024/07/14 03:20:11 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects/abstract_figure.h"
#include "objects/triangle.h"
#include "utils/vec3d.h"
#include "rt_errno.h"

static const t_abstract_figure_vtable	g_vtable = {
	.del = abstract_figure_del,
	.calculate_aabb = (void *)triangle_calculate_aabb,
	.intersect = (void *)triangle_intersect,
	.get_color = abstract_figure_get_color,
	.get_normal = (void *)triangle_get_normal,
};

t_rt_errno	triangle_init(t_triangle *self, t_triangle_init *args)
{
	t_rt_errno	ret;

	*self = (t_triangle){};
	ret = abstract_figure_init((t_abstract_figure *)self,
			&(t_abstract_figure_init){
			.color = args->color,
			.reflectivity = args->reflectivity,
			.checker = args->checker,
			.bump = args->bump,
		});
	if (ret)
		return (ret);
	((t_abstract_figure *)self)->_ = &g_vtable;
	self->a = args->first;
	self->ab = vec3d_sub(args->second, args->first);
	self->ac = vec3d_sub(args->third, args->first);
	self->normal = vec3d_norm(vec3d_cross(self->ab, self->ac));
	triangle_calculate_aabb(self);
	return (SUCCESS);
}
