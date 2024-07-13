/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 20:55:30 by hshimizu          #+#    #+#             */
/*   Updated: 2024/07/14 00:18:32 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects/abstract_figure.h"
#include "objects/texture.h"
#include "rt_errno.h"
#include "utils/vec3d.h"
#include <math.h>
#include <stdlib.h>

t_rt_errno	abstract_figure_init(t_abstract_figure *self,
		t_abstract_figure_init *args)
{
	t_rt_errno	ret;

	*self = (t_abstract_figure){};
	(void)args;
	self->aabb.min = (t_vec3d){{-INFINITY, -INFINITY, -INFINITY}};
	self->aabb.max = (t_vec3d){{INFINITY, INFINITY, INFINITY}};
	ret = texture_init(&self->texture, &(t_texture_init){
			.color = args->color,
			.reflectivity = args->reflectivity,
			.checker = args->checker,
			.bump = args->bump
		});
	if (ret)
		return (ret);
	return (SUCCESS);
}

void	abstract_figure_del(t_abstract_figure *self)
{
	texture_del(&self->texture);
}
