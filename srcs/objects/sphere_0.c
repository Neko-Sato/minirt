/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere_0.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 00:58:48 by hshimizu          #+#    #+#             */
/*   Updated: 2024/06/12 12:37:10 by hshimizu         ###   ########.fr       */
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
	((t_figure *)self)->_ = &vtable;
	self->diameter = 1.;
	return (NO_ERROR);
}

void	sphere_del(t_sphere *self)
{
	figure_del((t_figure *)self);
}
