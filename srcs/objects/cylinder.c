/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 00:58:41 by hshimizu          #+#    #+#             */
/*   Updated: 2024/06/07 16:24:42 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects/cylinder.h"
#include "objects/figure.h"
#include "rt_errno.h"
#include <stdlib.h>

int	cylinder_init(t_cylinder *self)
{
	static const t_figure_vtable	vtable = {
		.del = (void *)cylinder_del,
	};
	int								ret;

	*self = (t_cylinder){};
	ret = figure_init((t_figure *)self);
	if (ret)
		return (ret);
	((t_figure *)self)->__vtable = &vtable;
	self->axis = (t_vec3d){{0, 1, 0}};
	self->diameter = 5.;
	self->height = 10.;
	return (NO_ERROR);
}

void	cylinder_del(t_cylinder *self)
{
	figure_del((t_figure *)self);
}
