/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 03:58:12 by hshimizu          #+#    #+#             */
/*   Updated: 2024/06/08 05:15:31 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VEC3D_H
# define VEC3D_H

typedef struct s_vec3d
{
	float	_[3];
}			t_vec3d;

t_vec3d		vec3d_add(t_vec3d a, t_vec3d b);
t_vec3d		vec3d_sub(t_vec3d a, t_vec3d b);
t_vec3d		vec3d_mul(float n, t_vec3d a);
float		vec3d_dot(t_vec3d a, t_vec3d b);
t_vec3d		vec3d_cross(t_vec3d a, t_vec3d b);

float		vec3d_abs(t_vec3d vec);
t_vec3d		vec3d_norm(t_vec3d vec);

#endif