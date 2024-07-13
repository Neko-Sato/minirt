/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 00:58:48 by hshimizu          #+#    #+#             */
/*   Updated: 2024/07/14 03:19:39 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects/abstract_figure.h"
#include "objects/sphere.h"
#include "objects/texture.h"
#include "rt_errno.h"

static const t_abstract_figure_vtable	g_vtable = {
	.del = abstract_figure_del,
	.calculate_aabb = (void *)sphere_calculate_aabb,
	.intersect = (void *)sphere_intersect,
	.get_color = abstract_figure_get_color,
	.get_normal = (void *)sphere_get_normal,
};

t_rt_errno	sphere_init(t_sphere *self, t_sphere_init *args)
{
	t_rt_errno	ret;

	*self = (t_sphere){};
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
	if (args->diameter < 0)
		return (OUT_OF_RANGE);
	self->coord = args->coord;
	self->radius = args->diameter / 2.;
	sphere_calculate_aabb(self);
	return (SUCCESS);
}
