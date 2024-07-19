/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix3x3_transform.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 02:18:10 by hshimizu          #+#    #+#             */
/*   Updated: 2024/07/20 04:11:51 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_errno.h"
#include "utils/matrix3x3.h"
#include <math.h>

t_matrix3x3	matrix3x3_transform(t_vec3d a, t_vec3d b)
{
	return (matrix3x3_rotation_axis(
			acos(vec3d_dot(a, b) / (vec3d_abs(a) * vec3d_abs(b))),
			vec3d_cross(a, b)));
}

int	matrix3x3_orientation(const t_vec3d *r, const t_vec3d *u, const t_vec3d *f,
	t_matrix3x3 *transform)
{
	t_vec3d	t[3];

	if (!r + !u + !f != 1)
		return (-1);
	if (r)
		t[0] = vec3d_norm(*r);
	else
		t[0] = vec3d_norm(vec3d_cross(*u, *f));
	if (u)
		t[1] = vec3d_norm(*u);
	else
		t[1] = vec3d_norm(vec3d_cross(*f, *r));
	if (f)
		t[2] = vec3d_norm(*f);
	else
		t[2] = vec3d_norm(vec3d_cross(*r, *u));
	if (!vec3d_abs(t[0]) || !vec3d_abs(t[1]) || !vec3d_abs(t[2]))
		return (-1);
	*transform = (t_matrix3x3){{
	{t[0]._[0], t[1]._[0], t[2]._[0]},
	{t[0]._[1], t[1]._[1], t[2]._[1]},
	{t[0]._[2], t[1]._[2], t[2]._[2]},
	}};
	return (0);
}
