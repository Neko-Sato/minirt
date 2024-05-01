/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 04:05:16 by hshimizu          #+#    #+#             */
/*   Updated: 2024/05/02 04:42:02 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJECTS_H
# define OBJECTS_H

# include "parser.h"
# include "vec3d.h"

typedef struct s_ambient
{
	double					ratio;
	int						color;
}							t_ambient;

extern const t_parse_entry	g_parse_entry_ambient[];
extern const t_parse		g_parse_ambient;

typedef struct s_camera
{
	t_vec3d					coordinates;
	t_vec3d					orientation;
	int						fov;
}							t_camera;

extern const t_parse_entry	g_parse_entry_camera[];
extern const t_parse		g_parse_camera;

typedef struct s_light
{
	t_vec3d					coordinates;
	double					brightness;
	int						color;
}							t_light;

extern const t_parse_entry	g_parse_entry_light[];
extern const t_parse		g_parse_light;

typedef struct s_sphere
{
	t_vec3d					coordinates;
	double					diameter;
	int						color;
}							t_sphere;

extern const t_parse_entry	g_parse_entry_sphere[];
extern const t_parse		g_parse_sphere;

typedef struct s_plane
{
	t_vec3d					coordinates;
	t_vec3d					normal;
	int						color;
}							t_plane;

extern const t_parse_entry	g_parse_entry_plane[];
extern const t_parse		g_parse_plane;

typedef struct s_cylinder
{
	t_vec3d					coordinates;
	t_vec3d					axis;
	double					diameter;
	double					height;
	int						color;
}							t_cylinder;

extern const t_parse_entry	g_parse_entry_cylinder[];
extern const t_parse		g_parse_cylinder;

typedef enum e_objstype
{
	o_none = -1,
	o_ambient,
	o_camera,
	o_light,
	o_sphere,
	o_plane,
	o_cylinder,
}							t_objstype;

typedef union u_objsvalue
{
	t_ambient				ambient;
	t_camera				camera;
	t_light					light;
	t_sphere				sphere;
	t_plane					plane;
	t_cylinder				cylinder;
}							t_objsvalue;

typedef struct s_object
{
	t_objstype				type;
	t_objsvalue				value;
}							t_object;

extern const size_t			g_object_num;
extern const t_parse		*g_parse_objects[];

#endif
