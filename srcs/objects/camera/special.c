/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 22:50:33 by hshimizu          #+#    #+#             */
/*   Updated: 2024/08/01 22:33:30 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "constants.h"
#include "objects/camera.h"
#include "rt_errno.h"
#include "utils/mat3x3.h"
#include "utils/vec3.h"
#include <libft.h>
#include <unistd.h>

static inline t_rt_errno	make_transform(t_camera_init *args,
		t_mat3x3 *transform)
{
	t_vec3	f;
	t_vec3	u;
	t_vec3	r;

	f = vec3_norm(args->orient);
	r = vec3_cross(vec3_norm(args->up), f);
	if (!vec3_abs(r))
	{
		if (!ALTERNATIVE_UP_VECTOR)
			return (AMBIGUOUS_ORIENTATION);
		u = (t_vec3){{0, 1, 0}};
		r = vec3_cross(u, f);
		if (!vec3_abs(r))
			u = (t_vec3){{0, 0, 1}};
		r = vec3_cross(u, f);
	}
	u = vec3_cross(f, r);
	*transform = mat3x3_basis(r, u, f);
	return (SUCCESS);
}

t_rt_errno	camera_init(t_camera *self, t_camera_init *args)
{
	t_rt_errno	ret;

	*self = (t_camera){};
	if (args->width < 0 || args->height < 0)
		return (OUT_OF_RANGE);
	self->coord = args->coord;
	ret = make_transform(args, &self->transform);
	if (ret)
		return (ret);
	self->fov = ft_deg2rad(args->fov);
	self->width = args->width;
	self->height = args->height;
	return (SUCCESS);
}

void	camera_del(t_camera *self)
{
	(void)self;
}
