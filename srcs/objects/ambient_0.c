/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ambient_0.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 22:50:33 by hshimizu          #+#    #+#             */
/*   Updated: 2024/06/12 12:36:23 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects/ambient.h"
#include "rt_errno.h"

int	ambient_init(t_ambient *self)
{
	*self = (t_ambient){};
	self->ratio = 0.5;
	self->color = (t_color){.raw = COLOR_RAW_WHITE};
	return (NO_ERROR);
}

void	ambient_del(t_ambient *self)
{
	(void)self;
}
