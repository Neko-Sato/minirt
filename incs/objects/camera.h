/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 02:14:50 by hshimizu          #+#    #+#             */
/*   Updated: 2024/06/15 16:12:02 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CAMERA_H
# define CAMERA_H

# include "utils/vec3d.h"

# ifndef DEFAULT_WIDTH
#  define DEFAULT_WIDTH 1000
# endif
# ifndef DEFAULT_HEIGHT
#  define DEFAULT_HEIGHT 800
# endif

typedef struct s_camera
{
	t_vec3d	coordinates;
	t_vec3d	orientation;
	int		fov;
	int		width;
	int		height;
	float	dist;
}			t_camera;

int			camera_init(t_camera *self);
void		camera_del(t_camera *self);

#endif
