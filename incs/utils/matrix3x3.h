/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix3x3.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 04:32:33 by hshimizu          #+#    #+#             */
/*   Updated: 2024/07/22 04:35:45 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATRIX3X3_H
# define MATRIX3X3_H

# include "utils/vec3d.h"

typedef struct s_matrix3x3
{
	float	_[3][3];
}			t_matrix3x3;

t_matrix3x3	matrix3x3_add(t_matrix3x3 a, t_matrix3x3 b);
t_matrix3x3	matrix3x3_sub(t_matrix3x3 a, t_matrix3x3 b);
t_matrix3x3	matrix3x3_mul(t_matrix3x3 a, t_matrix3x3 b);
t_matrix3x3	matrix3x3_mul_scalar(float n, t_matrix3x3 a);
t_vec3d		matrix3x3_mul_vec3d(t_matrix3x3 a, t_vec3d b);

float		matrix3x3_det(t_matrix3x3 a);
t_matrix3x3	matrix3x3_adj(t_matrix3x3 a);
t_matrix3x3	matrix3x3_inv(t_matrix3x3 a);
t_matrix3x3	matrix3x3_transpose(t_matrix3x3 a);

t_matrix3x3	matrix3x3_rotation_x(float n);
t_matrix3x3	matrix3x3_rotation_y(float n);
t_matrix3x3	matrix3x3_rotation_z(float n);
t_matrix3x3	matrix3x3_rotation_rollpitchyaw(float roll, float pitch, float yaw);
t_matrix3x3	matrix3x3_rotation_axis(float n, t_vec3d axis);

t_matrix3x3	matrix3x3_transform(t_vec3d a, t_vec3d b);
t_matrix3x3	matrix3x3_basis(t_vec3d r, t_vec3d u, t_vec3d f);

#endif
