/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 00:58:48 by hshimizu          #+#    #+#             */
/*   Updated: 2024/06/07 16:24:23 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects/sphere.h"
#include "objects/figure.h"
#include "rt_errno.h"
#include <stdlib.h>

int	sphere_init(t_sphere *self)
{
	static const t_figure_vtable	vtable = {
		.del = (void *)sphere_del,
	};
	int								ret;

	*self = (t_sphere){};
	ret = figure_init((t_figure *)self);
	if (ret)
		return (ret);
	((t_figure *)self)->__vtable = &vtable;
	self->diameter = 1.;
	return (NO_ERROR);
}

void	sphere_del(t_sphere *self)
{
	figure_del((t_figure *)self);
}
