/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 20:59:23 by hshimizu          #+#    #+#             */
/*   Updated: 2024/07/12 21:32:37 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects/abstract_light.h"
#include "rt_errno.h"

t_rt_errno	abstract_light_init(t_abstract_light *self,
		t_abstract_light_init *args)
{
	*self = (t_abstract_light){};
	self->color = args->color;
	if (args->brightness < 0 || 1 < args->brightness)
		return (OUT_OF_RANGE);
	self->brightness = args->brightness;
	return (SUCCESS);
}

void	abstract_light_del(t_abstract_light *self)
{
	(void)self;
}
