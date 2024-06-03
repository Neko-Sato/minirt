/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 02:14:50 by hshimizu          #+#    #+#             */
/*   Updated: 2024/06/02 03:35:42 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CAMERA_H
# define CAMERA_H

# include "utils/vec3d.h"

typedef struct s_camera		t_camera;

typedef struct s_class_camera
{
	int						(*init)(t_camera *self);
	void					(*del)(t_camera *self);
}							t_class_camera;

int							__camera_init(t_camera *self);
void						__camera_del(t_camera *self);

extern const t_class_camera	g_class_camera;

typedef struct s_camera
{
	const t_class_camera	*__class;
	t_vec3d					coordinates;
	t_vec3d					orientation;
	int						fov;
}							t_camera;

#endif
