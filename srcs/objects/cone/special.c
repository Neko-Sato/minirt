/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 00:58:41 by hshimizu          #+#    #+#             */
/*   Updated: 2024/07/17 23:14:02 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects/abstract_figure.h"
#include "objects/cone.h"
#include "rt_errno.h"
#include "utils/matrix3x3.h"

static const t_abstract_figure_vtable	g_vtable = {
	.del = abstract_figure_del,
	.calculate_aabb = (void *)cone_calculate_aabb,
	.intersect = (void *)cone_intersect,
	.get_color = abstract_figure_get_color,
	.get_normal = (void *)cone_get_normal,
};

t_rt_errno	cone_init(t_cone *self, t_cone_init *args)
{
	t_rt_errno	ret;
	t_vec3d		tmp;

	if (args->diameter < 0)
		return (OUT_OF_RANGE);
	*self = (t_cone){};
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
	tmp = vec3d_sub(args->apex, args->coord);
	self->height = vec3d_abs(tmp);
	if (!self->height)
		return (AMBIGUOUS_ORIENTATION);
	self->axis = vec3d_norm(tmp);
	self->radius = args->diameter / 2.;
	cone_calculate_aabb(self);
	return (SUCCESS);
}
