/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 00:58:41 by hshimizu          #+#    #+#             */
/*   Updated: 2024/06/29 16:06:08 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects/cylinder.h"
#include "objects/figure.h"
#include "rt_errno.h"
#include "utils/matrix3x3.h"

static const t_figure_vtable	g_vtable = {
	.del = (void *)cylinder_del,
	.intersect = (void *)cylinder_intersect,
	.get_color = figure_get_color,
};

t_rt_errno	cylinder_init(t_cylinder *self, t_cylinder_init *args)
{
	t_rt_errno	ret;

	*self = (t_cylinder){};
	ret = figure_init((t_figure *)self, &(t_figure_init){
			.color = args->color,
			.opt = args->opt,
		});
	if (ret)
		return (ret);
	((t_figure *)self)->_ = &g_vtable;
	self->rotation = matrix3x3_transform(args->axis, (t_vec3d){{0, 1, 0}});
	self->r_coord = matrix3x3_mul_vec3d(self->rotation, args->coord);
	if (args->diameter < 0 || args->height < 0)
		return (OUT_OF_RANGE);
	self->height = args->height;
	self->radius = args->diameter / 2.;
	cylinder_set_aabb(self);
	return (SUCCESS);
}

void	cylinder_del(t_cylinder *self)
{
	figure_del((t_figure *)self);
}
