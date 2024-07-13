/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane_0.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 22:50:33 by hshimizu          #+#    #+#             */
/*   Updated: 2024/06/18 20:05:38 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects/abstract_figure.h"
#include "objects/plane.h"
#include "rt_errno.h"

static const t_abstract_figure_vtable	g_vtable = {
	.del = abstract_figure_del,
	.calculate_aabb = (void *)plane_calculate_aabb,
	.intersect = (void *)plane_intersect,
	.get_color = abstract_figure_get_color,
	.get_normal = (void *)plane_get_normal,
};

t_rt_errno	plane_init(t_plane *self, t_plane_init *args)
{
	t_rt_errno	ret;

	*self = (t_plane){};
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
	if (!vec3d_abs(args->orient))
		return (AMBIGUOUS_ORIENTATION);
	self->orient = vec3d_norm(args->orient);
	plane_calculate_aabb(self);
	return (SUCCESS);
}
