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
#include "utils/vec3.h"
#include "rt_errno.h"

static const t_abstract_figure_vtable	g_vtable = {
	.del = abstract_figure_del,
	.intersect = (void *)plane_intersect,
	.get_normal = (void *)plane_get_normal,
	.get_uv_coord = (void *)plane_get_uv_coord,
};

t_rt_errno	plane_init(t_plane *self, t_plane_init *args)
{
	t_rt_errno	ret;

	if (!vec3_abs(args->orient))
		return (AMBIGUOUS_ORIENTATION);
	*self = (t_plane){};
	ret = abstract_figure_init((void *)self,
			&(t_abstract_figure_init){
			.rotation = mat3x3_transform((t_vec3){{0, 1, 0}}, args->orient),
			.position = args->coord,
			.color = args->color,
			.reflectivity = args->reflectivity,
			.checker = args->checker,
		});
	if (ret)
		return (ret);
	((t_abstract_figure *)self)->_ = &g_vtable;
	plane_calculate_aabb(self);
	return (SUCCESS);
}
