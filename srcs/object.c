/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 06:41:36 by hshimizu          #+#    #+#             */
/*   Updated: 2024/05/16 17:14:39 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	object_parser(char *str, t_object *object)
{
	char	*identifier;

	object->type = o_none;
	identifier = ft_strsep(&str, RT_DELIMIITER);
	if (!identifier || *identifier == '#')
		return (NO_ERROR);
	return (object_parser_internal(identifier, str, object));
}

int	object_parser_internal(char *identifier, char *str, t_object *object)
{
	if (!ft_strcmp(IDENTIFIER_O_AMBIENT, identifier))
		return (o_ambient_parser(str, object));
	else if (!ft_strcmp(IDENTIFIER_O_CAMERA, identifier))
		return (o_camera_parser(str, object));
	else if (!ft_strcmp(IDENTIFIER_O_LIGHT, identifier))
		return (o_light_parser(str, object));
	else if (!ft_strcmp(IDENTIFIER_O_FIGURE, identifier))
		return (o_figure_parser(str, object));
	object->type = o_figure;
	return (figure_parser_internal(identifier, str,
			&object->value.figure.figure));
}
