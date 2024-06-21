/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_0.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 22:50:33 by hshimizu          #+#    #+#             */
/*   Updated: 2024/06/22 01:25:01 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects/camera.h"
#include "rt_errno.h"
#include <libft.h>
#include <math.h>

int	camera_init(t_camera *self)
{
	*self = (t_camera){};
	self->coordinates = (t_vec3d){{0, 0, 0}};
	self->transform = (t_matrix3x3){{{1, 0, 0}, {0, 1, 0}, {0, 0, 1}}};
	self->fov = ft_deg2rad(120);
	self->width = DEFAULT_WIDTH;
	self->height = DEFAULT_HEIGHT;
	self->dist = INFINITY;
	return (SUCCESS);
}

void	camera_del(t_camera *self)
{
	(void)self;
}

int	camera_transform(t_vec3d f, t_vec3d u, t_matrix3x3 *transform)
{
	const t_vec3d		_f = vec3d_norm(f);
	const t_vec3d		_r = vec3d_norm(vec3d_cross(u, f));
	const t_vec3d		_u = vec3d_norm(vec3d_cross(f, _r));
	const t_matrix3x3	tmp = {{
	{_r._[0], _u._[0], _f._[0]},
	{_r._[1], _u._[1], _f._[1]},
	{_r._[2], _u._[2], _f._[2]},
	}};

	if (!tmp._[0][0] && !tmp._[0][1] && !tmp._[0][2]
		&& !tmp._[1][0] && !tmp._[1][1] && !tmp._[1][2]
		&& !tmp._[1][0] && !tmp._[2][1] && !tmp._[2][2])
		return (AMBIGUOUS_ORIENTATION);
	if (isnan(tmp._[0][0]) || isnan(tmp._[0][1]) || isnan(tmp._[0][2])
		|| isnan(tmp._[1][0]) || isnan(tmp._[1][1]) || isnan(tmp._[1][2])
		|| isnan(tmp._[2][0]) || isnan(tmp._[2][1]) || isnan(tmp._[2][2]))
		return (AMBIGUOUS_ORIENTATION);
	*transform = tmp;
	return (SUCCESS);
}
