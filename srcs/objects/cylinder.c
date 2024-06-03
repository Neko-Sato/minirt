/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 00:58:41 by hshimizu          #+#    #+#             */
/*   Updated: 2024/06/04 02:39:16 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects/cylinder.h"
#include "rt_errno.h"
#include <stdlib.h>

const t_class_cylinder	g_class_cylinder = {
	.init = __cylinder_init,
	.del = __cylinder_del,
};

int	__cylinder_init(t_cylinder *self)
{
	int	ret;

	*self = (t_cylinder){};
	self->__class = &g_class_cylinder;
	ret = __figure_init(&self->__parent);
	if (ret)
		return (ret);
	self->axis = (t_vec3d){{0, 1, 0}};
	self->diameter = 5.;
	self->height = 10.;
	return (NO_ERROR);
}

void	__cylinder_del(t_cylinder *self)
{
	self->__parent.__class->del(&self->__parent);
}
