/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 22:50:33 by hshimizu          #+#    #+#             */
/*   Updated: 2024/07/05 08:45:55 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects/light.h"
#include "rt_errno.h"

t_rt_errno	light_init(t_light *self, t_light_init *args)
{
	*self = (t_light){};
	self->coord = args->coord;
	if (args->brightness < 0 || 1 < args->brightness)
		return (OUT_OF_RANGE);
	self->color = args->color;
	self->color._.alpha = 0xff * args->brightness;
	return (SUCCESS);
}

void	light_del(t_light *self)
{
	(void)self;
}
