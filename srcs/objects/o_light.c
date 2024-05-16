/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   o_light.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 22:02:57 by hshimizu          #+#    #+#             */
/*   Updated: 2024/05/16 08:32:59 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	o_light_parser(char *str, t_object *object)
{
	static const size_t			size = 3;
	static const t_parser_entry	entries[] = {
	{offsetof(t_o_light, coordinates), (t_parser_fun)parse_vec3d},
	{offsetof(t_o_light, brightness), (t_parser_fun)parse_rate},
	{offsetof(t_o_light, color), (t_parser_fun)parse_color},
	};
	t_o_light *const			light = &object->value.light;

	object->type = o_light;
	return (parser(str, entries, size, light));
}
