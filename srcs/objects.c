/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 04:16:35 by hshimizu          #+#    #+#             */
/*   Updated: 2024/05/02 07:05:33 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects.h"
#include "parser.h"

const t_parse_entry	g_parse_entry_ambient[] = {
{.dst_offset = offsetof(t_ambient, ratio),
	.parse_fun = (t_parse_fun)parse_ratio},
{.dst_offset = offsetof(t_ambient, color),
	.parse_fun = (t_parse_fun)parse_color},
};

const t_parse		g_parse_ambient = {
	.identifier = "A",
	.entry = g_parse_entry_ambient,
	.size = 2,
	.required = 2,
};

const t_parse_entry	g_parse_entry_camera[] = {
{.dst_offset = offsetof(t_camera, coordinates),
	.parse_fun = (t_parse_fun)parse_vec3d},
{.dst_offset = offsetof(t_camera, orientation),
	.parse_fun = (t_parse_fun)parse_normalized_vec3d},
{.dst_offset = offsetof(t_camera, fov),
	.parse_fun = (t_parse_fun)parse_fov},
};

const t_parse		g_parse_camera = {
	.identifier = "C",
	.entry = g_parse_entry_camera,
	.size = 3,
	.required = 3,
};

const t_parse_entry	g_parse_entry_light[] = {
{.dst_offset = offsetof(t_light, coordinates),
	.parse_fun = (t_parse_fun)parse_vec3d},
{.dst_offset = offsetof(t_light, brightness),
	.parse_fun = (t_parse_fun)parse_ratio},
{.dst_offset = offsetof(t_light, color),
	.parse_fun = (t_parse_fun)parse_color},
};

const t_parse		g_parse_light = {
	.identifier = "L",
	.entry = g_parse_entry_light,
	.size = 3,
	.required = 2,
};

const t_parse_entry	g_parse_entry_sphere[] = {
{.dst_offset = offsetof(t_sphere, coordinates),
	.parse_fun = (t_parse_fun)parse_vec3d},
{.dst_offset = offsetof(t_sphere, diameter),
	.parse_fun = (t_parse_fun)parse_double},
{.dst_offset = offsetof(t_sphere, color),
	.parse_fun = (t_parse_fun)parse_color},
};

const t_parse		g_parse_sphere = {
	.identifier = "sp",
	.entry = g_parse_entry_sphere,
	.size = 3,
	.required = 3,
};

const t_parse_entry	g_parse_entry_plane[] = {
{.dst_offset = offsetof(t_plane, coordinates),
	.parse_fun = (t_parse_fun)parse_vec3d},
{.dst_offset = offsetof(t_plane, normal),
	.parse_fun = (t_parse_fun)parse_normalized_vec3d},
{.dst_offset = offsetof(t_plane, color),
	.parse_fun = (t_parse_fun)parse_color},
};

const t_parse		g_parse_plane = {
	.identifier = "pl",
	.entry = g_parse_entry_plane,
	.size = 3,
	.required = 3,
};

const t_parse_entry	g_parse_entry_cylinder[] = {
{.dst_offset = offsetof(t_cylinder, coordinates),
	.parse_fun = (t_parse_fun)parse_vec3d},
{.dst_offset = offsetof(t_cylinder, axis),
	.parse_fun = (t_parse_fun)parse_normalized_vec3d},
{.dst_offset = offsetof(t_cylinder, diameter),
	.parse_fun = (t_parse_fun)parse_double},
{.dst_offset = offsetof(t_cylinder, height),
	.parse_fun = (t_parse_fun)parse_double},
{.dst_offset = offsetof(t_cylinder, color),
	.parse_fun = (t_parse_fun)parse_color},
};

const t_parse		g_parse_cylinder = {
	.identifier = "cy",
	.entry = g_parse_entry_cylinder,
	.size = 5,
	.required = 5,
};

const size_t		g_object_num = 6;

const t_parse		*g_parse_objects[] = {
	&g_parse_ambient,
	&g_parse_camera,
	&g_parse_light,
	&g_parse_sphere,
	&g_parse_plane,
	&g_parse_cylinder,
};
