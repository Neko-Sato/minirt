/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 03:58:12 by hshimizu          #+#    #+#             */
/*   Updated: 2024/07/20 20:22:48 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VEC3_H
# define VEC3_H

typedef struct s_vec3
{
	float	_[3];
}			t_vec3;

t_vec3		vec3_add(t_vec3 a, t_vec3 b);
t_vec3		vec3_sub(t_vec3 a, t_vec3 b);
t_vec3		vec3_mul(float n, t_vec3 a);
float		vec3_dot(t_vec3 a, t_vec3 b);
t_vec3		vec3_cross(t_vec3 a, t_vec3 b);

float		vec3_abs(t_vec3 vec);
t_vec3		vec3_norm(t_vec3 vec);
t_vec3		vec3_ortho(t_vec3 a, t_vec3 b);

t_vec3		vec3_reflect(t_vec3 i, t_vec3 n);

/*
	abs(r) -> abs(u x f)
	abs(u) -> abs(f x r)
	abs(f) -> abs(r x u)
*/

#endif