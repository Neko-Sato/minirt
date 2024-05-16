/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   o_camera.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 02:14:50 by hshimizu          #+#    #+#             */
/*   Updated: 2024/05/15 22:18:58 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef O_CAMERA_H
# define O_CAMERA_H

# include "utils/vec3d.h"

# define IDENTIFIER_O_CAMERA "C"

typedef struct s_o_camera
{
	t_vec3d				coordinates;
	t_vec3d				orientation;
	int					fov;
}						t_o_camera;

typedef struct s_object	t_object;

int						o_camera_parser(char *str, t_object *object);

#endif
