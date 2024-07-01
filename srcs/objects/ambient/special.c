/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 22:50:33 by hshimizu          #+#    #+#             */
/*   Updated: 2024/06/29 16:02:35 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects/ambient.h"
#include "rt_errno.h"

t_rt_errno	ambient_init(t_ambient *self, t_ambient_init *args)
{
	*self = (t_ambient){};
	if (args->ratio < 0 || 1 < args->ratio)
		return (OUT_OF_RANGE);
	self->ratio = args->ratio;
	self->color = args->color;
	return (SUCCESS);
}

void	ambient_del(t_ambient *self)
{
	(void)self;
}
