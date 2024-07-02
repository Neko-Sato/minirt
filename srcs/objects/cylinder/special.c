/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 00:58:41 by hshimizu          #+#    #+#             */
/*   Updated: 2024/07/03 07:09:40 by hshimizu         ###   ########.fr       */
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
	self->coord = args->coord;
	if (!vec3d_abs(args->axis))
		return (AMBIGUOUS_ORIENTATION);
	self->axis = vec3d_norm(args->axis);
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
