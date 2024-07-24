/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 02:14:50 by hshimizu          #+#    #+#             */
/*   Updated: 2024/07/23 02:12:34 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CAMERA_H
# define CAMERA_H

# include "rt_errno.h"
# include "utils/mat3x3.h"
# include "utils/vec3.h"

typedef struct s_camera
{
	t_vec3		coord;
	t_mat3x3	transform;
	float		fov;
	int			width;
	int			height;
}				t_camera;

typedef struct s_camera_init
{
	t_vec3		coord;
	t_vec3		orient;
	t_vec3		up;
	int			fov;
	int			width;
	int			height;
}				t_camera_init;

t_rt_errno		camera_init(\
	t_camera *self, t_camera_init *args);
void			camera_del(\
	t_camera *self);

void			camera_move(\
	t_camera *self, const t_vec3 *direction);
void			camera_rotate(\
	t_camera *self, float roll, float pitch, float yaw);
void			camera_set_fov(\
	t_camera *self, float fov);

#endif
