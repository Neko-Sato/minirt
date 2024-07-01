/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 22:50:33 by hshimizu          #+#    #+#             */
/*   Updated: 2024/06/29 16:10:34 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects/figure.h"
#include "objects/square.h"
#include "rt_errno.h"
#include <stdlib.h>

static const t_figure_vtable	g_vtable = {
	.del = (void *)square_del,
	.intersect = figure_intersect,
	.get_color = figure_get_color,
};

t_rt_errno	square_init(t_square *self, t_square_init *args)
{
	t_rt_errno	ret;

	*self = (t_square){};
	ret = figure_init((t_figure *)self, &(t_figure_init){
			.color = args->color,
			.opt = args->opt
		});
	if (ret)
		return (ret);
	((t_figure *)self)->_ = &g_vtable;
	if (!vec3d_abs(args->orient))
		return (AMBIGUOUS_ORIENTATION);
	if (args->size < 0)
		return (OUT_OF_RANGE);
	self->coord = args->coord;
	self->orient = vec3d_norm(args->orient);
	self->size = self->size;
	return (SUCCESS);
}

void	square_del(t_square *self)
{
	figure_del((t_figure *)self);
}
