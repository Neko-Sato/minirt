/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 22:50:33 by hshimizu          #+#    #+#             */
/*   Updated: 2024/08/01 22:40:54 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects/abstract_figure.h"
#include "objects/triangle.h"
#include "utils/vec3.h"
#include "rt_errno.h"

static const t_abstract_figure_vtable	g_vtable = {
	.del = abstract_figure_del,
	.intersect = (void *)triangle_intersect,
	.get_normal = (void *)triangle_get_normal,
	.get_uv_coord = (void *)triangle_get_uv_coord,
};

static inline t_mat3x3	make_rotation(t_triangle_init *args)
{
	const t_vec3	ab = vec3_sub(args->second, args->first);
	const t_vec3	ac = vec3_sub(args->third, args->first);

	return (mat3x3_basis(ac, ab, vec3_cross(ac, ab)));
}

t_rt_errno	triangle_init(t_triangle *self, t_triangle_init *args)
{
	t_rt_errno	ret;

	*self = (t_triangle){};
	ret = abstract_figure_init((t_abstract_figure *)self,
			&(t_abstract_figure_init){
			.rotation = make_rotation(args),
			.position = args->first,
			.color = args->color,
			.reflectivity = args->reflectivity,
			.checker = args->checker,
		});
	if (ret)
		return (ret);
	((t_abstract_figure *)self)->_ = &g_vtable;
	triangle_calculate_aabb(self);
	return (SUCCESS);
}
