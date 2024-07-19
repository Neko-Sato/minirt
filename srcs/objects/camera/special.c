/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 22:50:33 by hshimizu          #+#    #+#             */
/*   Updated: 2024/07/20 04:13:09 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects/camera.h"
#include "constants.h"
#include "rt_errno.h"
#include "utils/matrix3x3.h"
#include <unistd.h>
#include <libft.h>

t_rt_errno	camera_init(t_camera *self, t_camera_init *args)
{
	if (!vec3d_abs(args->orient) || !vec3d_abs(args->up))
		return (AMBIGUOUS_ORIENTATION);
	if (!ALLOW_FOV_UNLIMITED && (args->fov < 0 || 180 < args->fov))
		return (OUT_OF_RANGE);
	if (args->width < 0 || args->height < 0)
		return (OUT_OF_RANGE);
	*self = (t_camera){};
	self->coord = args->coord;
	if (matrix3x3_orientation(NULL, &args->up, &args->orient, &self->transform))
		return (AMBIGUOUS_ORIENTATION);
	self->fov = ft_deg2rad(args->fov);
	self->width = args->width;
	self->height = args->height;
	return (SUCCESS);
}

void	camera_del(t_camera *self)
{
	(void)self;
}
