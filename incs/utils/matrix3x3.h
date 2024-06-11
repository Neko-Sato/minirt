/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix3x3.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 04:32:33 by hshimizu          #+#    #+#             */
/*   Updated: 2024/06/09 18:04:57 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATRIX3X3_H
# define MATRIX3X3_H

/*
	I've introduced a matrix to move it....
*/

# include "utils/vec3d.h"

typedef struct s_matrix3x3
{
	float	_[3][3];
}				t_matrix3x3;

t_matrix3x3		matrix3x3_add(t_matrix3x3 a, t_matrix3x3 b);
t_matrix3x3		matrix3x3_sub(t_matrix3x3 a, t_matrix3x3 b);
t_matrix3x3		matrix3x3_mul(t_matrix3x3 a, t_matrix3x3 b);
t_matrix3x3		matrix3x3_mul_scalar(float n, t_matrix3x3 a);
t_vec3d			matrix3x3_mul_vec3d(t_matrix3x3 a, t_vec3d b);

t_matrix3x3		matrix3x3_rotation_x(float n);
t_matrix3x3		matrix3x3_rotation_y(float n);
t_matrix3x3		matrix3x3_rotation_z(float n);
t_matrix3x3		matrix3x3_rotation_axis(float n, t_vec3d axis);

#endif
