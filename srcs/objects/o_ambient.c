/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   o_ambient.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 22:02:57 by hshimizu          #+#    #+#             */
/*   Updated: 2024/05/16 08:34:09 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	o_ambient_parser(char *str, t_object *object)
{
	static const size_t			size = 2;
	static const t_parser_entry	entries[] = {
	{offsetof(t_o_ambient, ratio), (t_parser_fun)parse_rate},
	{offsetof(t_o_ambient, color), (t_parser_fun)parse_color},
	};
	t_o_ambient *const			ambient = &object->value.ambient;

	object->type = o_ambient;
	return (parser(str, entries, size, ambient));
}
