/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ambient.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 22:50:33 by hshimizu          #+#    #+#             */
/*   Updated: 2024/06/04 02:38:32 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects/ambient.h"
#include "rt_errno.h"
#include <stdlib.h>

const t_class_ambient	g_class_ambient = {
	.init = __ambient_init,
	.del = __ambient_del,
};

int	__ambient_init(t_ambient *self)
{
	*self = (t_ambient){};
	self->__class = &g_class_ambient;
	self->ratio = 0.5;
	self->color = (t_color){.raw = COLOR_RAW_WHITE};
	return (NO_ERROR);
}

void	__ambient_del(t_ambient *self)
{
	(void)self;
}
