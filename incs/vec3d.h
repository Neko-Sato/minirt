/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 03:58:12 by hshimizu          #+#    #+#             */
/*   Updated: 2024/05/01 06:35:38 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VEC3D_H
# define VEC3D_H

typedef struct s_vec3d
{
	double	x;
	double	y;
	double	z;
}			t_vec3d;

typedef union u_vec3d_array
{
	t_vec3d	value;
	double	array[3];
}			t_vec3d_array;

double		vec3d_abs(t_vec3d vec);
t_vec3d		vec3d_normalize(t_vec3d vec);

#endif