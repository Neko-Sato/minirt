/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f_plane.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 22:32:31 by hshimizu          #+#    #+#             */
/*   Updated: 2024/05/16 08:37:43 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	f_plane_parser(char *str, t_figure *figure)
{
	static const size_t			size = 3;
	static const t_parser_entry	entries[] = {
	{offsetof(t_f_plane, coordinates), (t_parser_fun)parse_vec3d},
	{offsetof(t_f_plane, normal), (t_parser_fun)parse_norm_vec3d},
	{offsetof(t_f_plane, texture), (t_parser_fun)texture_parser},
	};
	t_f_plane *const			sphere = &figure->value.plane;

	figure->type = f_plane;
	return (parser(str, entries, size, sphere));
}
