/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   figure.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 22:02:57 by hshimizu          #+#    #+#             */
/*   Updated: 2024/05/16 08:56:42 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <libft.h>

int	figure_parser(char *str, t_figure *figure)
{
	char	*identifier;

	identifier = ft_strsep(&str, RT_DELIMIITER);
	if (!identifier)
		return (INCORRECT_FORMAT);
	return (figure_parser_internal(identifier, str, figure));
}

int	figure_parser_internal(char *identifier, char *str, t_figure *figure)
{
	if (!ft_strcmp(IDENTIFIER_F_SPHERE, identifier))
		return (f_sphere_parser(str, figure));
	else if (!ft_strcmp(IDENTIFIER_F_PLANE, identifier))
		return (f_plane_parser(str, figure));
	else if (!ft_strcmp(IDENTIFIER_F_CYLINDER, identifier))
		return (f_cylinder_parser(str, figure));
	return (INCORRECT_FORMAT);
}
