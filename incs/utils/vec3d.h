/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 03:58:12 by hshimizu          #+#    #+#             */
/*   Updated: 2024/05/16 01:35:22 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VEC3D_H
# define VEC3D_H

typedef struct s_vec3d
{
	long double	_[3];
}				t_vec3d;

t_vec3d			vec3d_add(t_vec3d a, t_vec3d b);
t_vec3d			vec3d_sub(t_vec3d a, t_vec3d b);
t_vec3d			vec3d_mul(long double n, t_vec3d a);
long double		vec3d_dot(t_vec3d a, t_vec3d b);
t_vec3d			vec3d_cross(t_vec3d a, t_vec3d b);

long double		vec3d_abs(t_vec3d vec);
t_vec3d			vec3d_norm(t_vec3d vec);

#endif