/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 04:05:16 by hshimizu          #+#    #+#             */
/*   Updated: 2024/04/27 04:38:16 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJECT_H
# define OBJECT_H

# include "vec3d.h"

# define IDENTIFIER_AMBIENT "A"
# define IDENTIFIER_CAMERA "C"
# define IDENTIFIER_LIGHT "L"
# define IDENTIFIER_SPHERE "sp"
# define IDENTIFIER_PLANE "pl"
# define IDENTIFIER_CYLINDER "cy"

// Csonfig
typedef struct s_ambient
{
	double		ratio;
	int			color;
}				t_ambient;

typedef struct s_camera
{
	t_vec3d		coord;
	t_vec3d		direction;
	int			fov;
}				t_camera;

// Light
typedef struct s_light
{
	t_vec3d		coord;
	double		ratio;
	int			color;
}				t_light;

// Figure
typedef struct s_sphere
{
	t_vec3d		coord;
	double		diameter;
	int			color;
}				t_sphere;

typedef struct s_plane
{
	t_vec3d		coord;
	t_vec3d		direction;
	int			color;
}				t_plane;

typedef struct s_cylinder
{
	t_vec3d		coord;
	t_vec3d		direction;
	double		diameter;
	double		height;
	int			color;
}				t_cylinder;

typedef enum e_objstype
{
	o_ambient,
	o_camera,
	o_light,
	o_sphere,
	o_plane,
	o_cylinder,
}				t_objstype;

typedef union u_objsvalue
{
	t_ambient	*ambient;
	t_camera	*camera;
	t_light		*light;
	t_sphere	*sphere;
	t_plane		*plane;
	t_cylinder	*cylinder;
}				t_objsvalue;

typedef struct s_object
{
	t_objstype	type;
	t_objsvalue	value;
}				t_object;

#endif
