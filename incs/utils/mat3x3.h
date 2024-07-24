/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mat3x3.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 04:32:33 by hshimizu          #+#    #+#             */
/*   Updated: 2024/07/23 01:47:34 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAT3X3_H
# define MAT3X3_H

# include "utils/vec3.h"

typedef struct s_mat3x3
{
	float	_[3][3];
}			t_mat3x3;

t_mat3x3	mat3x3_add(t_mat3x3 a, t_mat3x3 b);
t_mat3x3	mat3x3_sub(t_mat3x3 a, t_mat3x3 b);
t_mat3x3	mat3x3_mul(t_mat3x3 a, t_mat3x3 b);
t_mat3x3	mat3x3_mul_scalar(float n, t_mat3x3 a);
t_vec3		mat3x3_mul_vec3(t_mat3x3 a, t_vec3 b);

float		mat3x3_det(t_mat3x3 a);
t_mat3x3	mat3x3_adj(t_mat3x3 a);
t_mat3x3	mat3x3_inv(t_mat3x3 a);
t_mat3x3	mat3x3_transpose(t_mat3x3 a);

t_mat3x3	mat3x3_rotation_x(float n);
t_mat3x3	mat3x3_rotation_y(float n);
t_mat3x3	mat3x3_rotation_z(float n);
t_mat3x3	mat3x3_rotation_rollpitchyaw(float roll, float pitch, float yaw);
t_mat3x3	mat3x3_rotation_axis(float n, t_vec3 axis);

t_mat3x3	mat3x3_transform(t_vec3 a, t_vec3 b);
t_mat3x3	mat3x3_basis(t_vec3 r, t_vec3 u, t_vec3 f);

#endif
