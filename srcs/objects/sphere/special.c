/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 00:58:48 by hshimizu          #+#    #+#             */
/*   Updated: 2024/08/01 22:40:46 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects/abstract_figure.h"
#include "objects/sphere.h"
#include "utils/vec3.h"
#include "utils/mat3x3.h"
#include "rt_errno.h"

static const t_abstract_figure_vtable	g_vtable = {
	.del = abstract_figure_del,
	.intersect = (void *)sphere_intersect,
	.get_normal = (void *)sphere_get_normal,
	.get_uv_coord = (void *)sphere_get_uv_coord,
};

t_rt_errno	sphere_init(t_sphere *self, t_sphere_init *args)
{
	t_rt_errno	ret;

	if (args->diameter < 0)
		return (OUT_OF_RANGE);
	*self = (t_sphere){};
	ret = abstract_figure_init((void *)self,
			&(t_abstract_figure_init){
			.rotation = mat3x3_mul_scalar(args->diameter / 2., \
					(t_mat3x3){{{1, 0, 0}, {0, 1, 0}, {0, 0, -1}}}),
			.position = args->coord,
			.color = args->color,
			.reflectivity = args->reflectivity,
			.checker = args->checker,
		});
	if (ret)
		return (ret);
	((t_abstract_figure *)self)->_ = &g_vtable;
	sphere_calculate_aabb(self);
	return (SUCCESS);
}
