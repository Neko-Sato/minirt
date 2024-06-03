/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 00:58:48 by hshimizu          #+#    #+#             */
/*   Updated: 2024/06/04 02:40:37 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects/sphere.h"
#include "rt_errno.h"
#include <stdlib.h>

const t_class_sphere	g_class_sphere = {
	.init = __sphere_init,
	.del = __sphere_del,
};

int	__sphere_init(t_sphere *self)
{
	int	ret;

	*self = (t_sphere){};
	self->__class = &g_class_sphere;
	ret = __figure_init(&self->__parent);
	if (ret)
		return (ret);
	self->diameter = 1.;
	return (NO_ERROR);
}

void	__sphere_del(t_sphere *self)
{
	self->__parent.__class->del(&self->__parent);
}
