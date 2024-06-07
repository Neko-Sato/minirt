/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix3x3.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 04:32:33 by hshimizu          #+#    #+#             */
/*   Updated: 2024/06/06 07:36:29 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATRIX3X3_H
# define MATRIX3X3_H

# include "utils/vec3d.h"

typedef struct s_matrix3x3
{
	long double	_[3][3];
}				t_matrix3x3;

t_matrix3x3		matrix3x3_add(t_matrix3x3 a, t_matrix3x3 b);
t_matrix3x3		matrix3x3_sub(t_matrix3x3 a, t_matrix3x3 b);
t_matrix3x3		matrix3x3_mul(t_matrix3x3 a, t_matrix3x3 b);
t_matrix3x3		matrix3x3_mul_scalar(long double n, t_matrix3x3 a);
t_vec3d			matrix3x3_mul_vec3d(t_matrix3x3 a, t_vec3d b);

t_matrix3x3		matrix3x3_rotation(long double x, long double y, long double z);
t_matrix3x3		matrix3x3_rotation_axis(long double n, t_vec3d axis);

#endif
