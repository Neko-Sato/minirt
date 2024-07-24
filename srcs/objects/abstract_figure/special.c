/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 20:55:30 by hshimizu          #+#    #+#             */
/*   Updated: 2024/07/25 02:30:13 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects/abstract_figure.h"
#include "rt_errno.h"
#include "utils/vec3.h"
#include "utils/mat3x3.h"
#include <math.h>
#include <stdlib.h>

t_rt_errno	abstract_figure_init(t_abstract_figure *self,
		t_abstract_figure_init *args)
{
	if (args->reflectivity < 0. || 1. < args->reflectivity)
		return (OUT_OF_RANGE);
	*self = (t_abstract_figure){};
	self->rotation = args->rotation;
	self->rotation_inv = mat3x3_inv(self->rotation);
	self->position = args->position;
	self->aabb.min = (t_vec3){{-__FLT_MAX__, -__FLT_MAX__, -__FLT_MAX__}};
	self->aabb.max = (t_vec3){{__FLT_MAX__, __FLT_MAX__, __FLT_MAX__}};
	self->color = args->color;
	self->reflectivity = args->reflectivity;
	self->checker = args->checker;
	self->bump = args->bump;
	return (SUCCESS);
}

void	abstract_figure_del(t_abstract_figure *self)
{
	free(self->bump);
}
