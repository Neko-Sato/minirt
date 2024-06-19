/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 19:23:41 by hshimizu          #+#    #+#             */
/*   Updated: 2024/06/19 16:14:10 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "rt_errno.h"
#include <libft.h>

int	parse_line(char **str, t_scene *scene)
{
	int		ret;
	char	*s;

	s = *str;
	ret = parse_blank(&s);
	if (ret != SUCCESS && ret != INCORRECT_FORMAT)
		return (ret);
	ret = parse_eol(&s);
	if (ret == INCORRECT_FORMAT)
	{
		ret = parse_object(&s, scene);
		if (ret)
			return (ret);
		ret = parse_blank(&s);
		if (ret != SUCCESS && ret != INCORRECT_FORMAT)
			return (ret);
		ret = parse_eol(&s);
	}
	if (ret)
		return (ret);
	*str = s;
	return (ret);
}

int	parse_object(char **str, t_scene *scene)
{
	static int (*const	parsers[])(char **, t_scene *) = {
		parse_ambient, parse_camera, parse_light,
		parse_sphere, parse_plane, parse_cylinder,
		parse_square, parse_triangle};
	int					ret;
	char				*s;
	t_identifier		identifier;

	s = *str;
	ret = parse_identifier(&s, &identifier);
	if (ret)
		return (ret);
	ret = parse_blank(&s);
	if (ret)
		return (ret);
	ret = (parsers[identifier])(&s, scene);
	if (ret)
		return (ret);
	*str = s;
	return (SUCCESS);
}

int	parse_eol(char **str)
{
	char	*s;

	s = *str;
	if (!ft_strchr("#\n", *s))
		return (INCORRECT_FORMAT);
	while (*s)
		s++;
	*str = s;
	return (SUCCESS);
}
