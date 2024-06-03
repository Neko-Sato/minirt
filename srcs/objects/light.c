/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 22:50:33 by hshimizu          #+#    #+#             */
/*   Updated: 2024/06/04 02:39:41 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects/light.h"
#include "rt_errno.h"
#include <stdlib.h>

const t_class_light	g_class_light = {
	.init = __light_init,
	.del = __light_del,
};

int	__light_init(t_light *self)
{
	*self = (t_light){};
	self->__class = &g_class_light;
	self->coordinates = (t_vec3d){{0, 100, 0}};
	self->brightness = 1.;
	self->color = (t_color){.raw = COLOR_RAW_WHITE};
	return (NO_ERROR);
}

void	__light_del(t_light *self)
{
	(void)self;
}
