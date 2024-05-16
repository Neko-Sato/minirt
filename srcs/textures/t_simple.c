/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_simple.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 22:51:20 by hshimizu          #+#    #+#             */
/*   Updated: 2024/05/16 08:44:30 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	t_simple_parser(char *str, t_texture *texture)
{
	static const size_t			size = 1;
	static const t_parser_entry	entries[] = {
	{offsetof(t_t_simple, color), (t_parser_fun)parse_color},
	};
	t_t_simple *const			simple = &texture->value.simple;

	texture->type = t_simple;
	return (parser(str, entries, size, simple));
}
