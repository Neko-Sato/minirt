/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 22:50:33 by hshimizu          #+#    #+#             */
/*   Updated: 2024/07/23 02:12:34 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects/camera.h"
#include "rt_errno.h"
#include "utils/vec3.h"
#include "utils/mat3x3.h"
#include <unistd.h>
#include <libft.h>

t_rt_errno	camera_init(t_camera *self, t_camera_init *args)
{
	*self = (t_camera){};
	if (args->width < 0 || args->height < 0)
		return (OUT_OF_RANGE);
	self->coord = args->coord;
	self->transform = mat3x3_basis(
			vec3_cross(args->up, args->orient), args->up, args->orient);
	self->fov = ft_deg2rad(args->fov);
	self->width = args->width;
	self->height = args->height;
	return (SUCCESS);
}

void	camera_del(t_camera *self)
{
	(void)self;
}
