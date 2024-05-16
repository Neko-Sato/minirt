/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f_spere.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 22:32:31 by hshimizu          #+#    #+#             */
/*   Updated: 2024/05/16 08:18:31 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	f_sphere_parser(char *str, t_figure *figure)
{
	static const size_t			size = 3;
	static const t_parser_entry	entries[] = {
	{offsetof(t_f_sphere, coordinates), (t_parser_fun)parse_vec3d},
	{offsetof(t_f_sphere, diameter), (t_parser_fun)parse_dobule},
	{offsetof(t_f_sphere, texture), (t_parser_fun)texture_parser},
	};
	t_f_sphere *const			sphere = &figure->value.sphere;

	figure->type = f_sphere;
	return (parser(str, entries, size, sphere));
}
