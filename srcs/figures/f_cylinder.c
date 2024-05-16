/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f_cylinder.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 22:32:31 by hshimizu          #+#    #+#             */
/*   Updated: 2024/05/16 08:39:37 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	f_cylinder_parser(char *str, t_figure *figure)
{
	static const size_t			size = 5;
	static const t_parser_entry	entries[] = {
	{offsetof(t_f_cylinder, coordinates), (t_parser_fun)parse_vec3d},
	{offsetof(t_f_cylinder, axis), (t_parser_fun)parse_norm_vec3d},
	{offsetof(t_f_cylinder, diameter), (t_parser_fun)parse_dobule},
	{offsetof(t_f_cylinder, height), (t_parser_fun)parse_dobule},
	{offsetof(t_f_cylinder, texture), (t_parser_fun)texture_parser},
	};
	t_f_cylinder *const			cylinder = &figure->value.cylinder;

	figure->type = f_cylinder;
	return (parser(str, entries, size, cylinder));
}
