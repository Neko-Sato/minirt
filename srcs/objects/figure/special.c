/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 00:58:30 by hshimizu          #+#    #+#             */
/*   Updated: 2024/06/29 16:06:31 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects/figure.h"
#include "rt_errno.h"
#include <math.h>
#include <libft.h>
#include <stdlib.h>

t_rt_errno	figure_init(t_figure *self, t_figure_init *args)
{
	*self = (t_figure){};
	self->color = args->color;
	if (args->opt.reflectivity < 0 || 1 < args->opt.reflectivity)
		return (OUT_OF_RANGE);
	self->reflectivity = args->opt.reflectivity;
	self->color = args->color;
	self->checker = args->opt.checker;
	self->bump = args->opt.bump;
	self->aabb[0] = (t_vec3d){{-INFINITY, -INFINITY, -INFINITY}};
	self->aabb[1] = (t_vec3d){{INFINITY, INFINITY, INFINITY}};
	return (SUCCESS);
}

void	figure_del(t_figure *self)
{
	free(self->bump);
}
