/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_0.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 22:50:33 by hshimizu          #+#    #+#             */
/*   Updated: 2024/06/19 16:14:10 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects/light.h"
#include "rt_errno.h"

int	light_init(t_light *self)
{
	*self = (t_light){};
	self->coordinates = (t_vec3d){{0, 100, 0}};
	self->brightness = 1.;
	self->color = (t_color){.raw = COLOR_RAW_WHITE};
	return (SUCCESS);
}

void	light_del(t_light *self)
{
	(void)self;
}
