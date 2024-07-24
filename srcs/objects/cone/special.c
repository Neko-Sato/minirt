/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 00:58:41 by hshimizu          #+#    #+#             */
/*   Updated: 2024/07/24 08:29:18 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects/abstract_figure.h"
#include "objects/cone.h"
#include "rt_errno.h"
#include "utils/mat3x3.h"

static const t_abstract_figure_vtable	g_vtable = {
	.del = abstract_figure_del,
	.intersect = (void *)cone_intersect,
	.get_normal = (void *)cone_get_normal,
	.get_uv_coord = (void *)cone_get_uv_coord,
};

static inline t_mat3x3	make_rotation(t_cone_init *args)
{
	const t_vec3	axis = vec3_sub(args->apex, args->coord);
	const t_mat3x3	rotation = mat3x3_transform(
			(t_vec3){{0, 1, 0}}, vec3_norm(axis));
	const t_mat3x3	transform = {{
	{args->diameter / 2., 0, 0},
	{0, vec3_abs(axis), 0},
	{0, 0, args->diameter / 2.}
	}};

	return (mat3x3_mul(rotation, transform));
}

t_rt_errno	cone_init(t_cone *self, t_cone_init *args)
{
	t_rt_errno	ret;

	if (args->diameter < 0)
		return (OUT_OF_RANGE);
	*self = (t_cone){};
	ret = abstract_figure_init((t_abstract_figure *)self,
			&(t_abstract_figure_init){
			.rotation = make_rotation(args),
			.position = args->coord,
			.color = args->color,
			.reflectivity = args->reflectivity,
			.checker = args->checker,
			.bump = args->bump,
		});
	if (ret)
		return (ret);
	((t_abstract_figure *)self)->_ = &g_vtable;
	cone_calculate_aabb(self);
	return (SUCCESS);
}
