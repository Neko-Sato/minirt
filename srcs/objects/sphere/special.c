/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 00:58:48 by hshimizu          #+#    #+#             */
/*   Updated: 2024/07/05 18:38:35 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects/figure.h"
#include "objects/sphere.h"
#include "rt_errno.h"

static const t_figure_vtable	g_vtable = {
	.del = (void *)sphere_del,
	.intersect = (void *)sphere_intersect,
	.get_color = figure_get_color,
	.get_normal = (void *)sphere_get_normal,
};

t_rt_errno	sphere_init(t_sphere *self, t_sphere_init *args)
{
	t_rt_errno	ret;

	*self = (t_sphere){};
	ret = figure_init((t_figure *)self, &(t_figure_init){
			.color = args->color,
			.opt = args->opt,
		});
	if (ret)
		return (ret);
	((t_figure *)self)->_ = &g_vtable;
	if (ret)
		return (ret);
	if (args->diameter < 0 || args->diameter < 0)
		return (OUT_OF_RANGE);
	self->coord = args->coord;
	self->radius = args->diameter / 2.;
	sphere_set_aabb(self);
	return (SUCCESS);
}

void	sphere_del(t_sphere *self)
{
	figure_del((t_figure *)self);
}
