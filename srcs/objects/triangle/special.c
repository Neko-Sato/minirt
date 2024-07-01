/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 22:50:33 by hshimizu          #+#    #+#             */
/*   Updated: 2024/06/29 01:17:39 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects/figure.h"
#include "objects/triangle.h"
#include "rt_errno.h"
#include <math.h>
#include <stdlib.h>

static const t_figure_vtable	g_vtable = {
	.del = (void *)triangle_del,
	.intersect = figure_intersect,
	.get_color = figure_get_color,
};

t_rt_errno	triangle_init(t_triangle *self, t_triangle_init *args)
{
	t_rt_errno	ret;

	*self = (t_triangle){};
	ret = figure_init((t_figure *)self, &(t_figure_init){
			.color = args->color,
			.opt = args->opt,
		});
	if (ret)
		return (ret);
	((t_figure *)self)->_ = &g_vtable;
	self->first = args->first;
	self->second = args->second;
	self->third = args->third;
	return (SUCCESS);
}

void	triangle_del(t_triangle *self)
{
	figure_del((t_figure *)self);
}
