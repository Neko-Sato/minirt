/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 21:06:37 by hshimizu          #+#    #+#             */
/*   Updated: 2024/07/14 03:35:24 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects/texture.h"
#include <libft.h>
#include <stdlib.h>

t_rt_errno	texture_init(t_texture *self, t_texture_init *args)
{
	*self = (t_texture){};
	self->color = args->color;
	if (args->reflectivity < 0 || 1 < args->reflectivity)
		return (OUT_OF_RANGE);
	self->reflectivity = args->reflectivity;
	self->checker = args->checker;
	self->bump = args->bump;
	return (SUCCESS);
}

void	texture_del(t_texture *self)
{
	free(self->bump);
}
