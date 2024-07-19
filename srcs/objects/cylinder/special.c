/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 00:58:41 by hshimizu          #+#    #+#             */
/*   Updated: 2024/07/20 04:39:26 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects/abstract_figure.h"
#include "objects/cylinder.h"
#include "rt_errno.h"
#include "utils/matrix3x3.h"

static const t_abstract_figure_vtable	g_vtable = {
	.del = abstract_figure_del,
	.calculate_aabb = (void *)cylinder_calculate_aabb,
	.intersect = (void *)cylinder_intersect,
	.get_color = abstract_figure_get_color,
	.get_normal = (void *)cylinder_get_normal,
	.get_uv_coord = (void *)cylinder_get_uv_coord,
};

t_rt_errno	cylinder_init(t_cylinder *self, t_cylinder_init *args)
{
	t_rt_errno	ret;

	if (args->diameter < 0 || args->height < 0)
		return (OUT_OF_RANGE);
	if (!vec3d_abs(args->axis))
		return (AMBIGUOUS_ORIENTATION);
	*self = (t_cylinder){};
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
	self->coord = args->coord;
	self->axis = vec3d_norm(args->axis);
	self->height = args->height;
	self->radius = args->diameter / 2.;
	cylinder_calculate_aabb(self);
	return (SUCCESS);
}
