/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 22:50:33 by hshimizu          #+#    #+#             */
/*   Updated: 2024/07/02 00:44:39 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects/camera.h"
#include "objects/minirt.h"
#include "rt_errno.h"
#include "utils/matrix3x3.h"
#include <libft.h>
#include <unistd.h>

t_rt_errno	camera_init(t_camera *self, t_camera_init *args)
{
	*self = (t_camera){};
	self->coord = self->coord;
	if (!vec3d_abs(args->orient) || !vec3d_abs(args->up))
		return (AMBIGUOUS_ORIENTATION);
	if (matrix3x3_orientation(args->orient, args->up, &self->transform))
	{
		if (!ALTERNATIVE_UP_VECTOR)
			return (AMBIGUOUS_ORIENTATION);
		(void)(matrix3x3_orientation(args->orient, (t_vec3d){{0, 1, 0}},
				&self->transform) && matrix3x3_orientation(args->orient,
				(t_vec3d){{1, 0, 0}}, &self->transform));
		ft_putendl_fd("Using alternative up vector.", STDERR_FILENO);
	}
	if (!ALLOW_FOV_UNLIMITED && (args->fov < 0 || 180 < args->fov))
		return (OUT_OF_RANGE);
	self->fov = ft_deg2rad(args->fov);
	if (self->width < 0 || self->height < 0 || self->dist < 0)
		return (OUT_OF_RANGE);
	self->width = args->width;
	self->height = args->height;
	self->dist = args->dist;
	return (SUCCESS);
}

void	camera_del(t_camera *self)
{
	(void)self;
}
