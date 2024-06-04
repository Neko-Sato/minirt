/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 19:23:41 by hshimizu          #+#    #+#             */
/*   Updated: 2024/06/05 04:24:56 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "rt_errno.h"
#include <libft.h>

int	take_line(char **str, t_scene *scene)
{
	int		ret;
	char	*s;

	s = *str;
	ret = take_blank(&s);
	if (ret != NO_ERROR && ret != INCORRECT_FORMAT)
		return (ret);
	ret = take_eol(&s);
	if (ret == INCORRECT_FORMAT)
	{
		ret = take_object(&s, scene);
		if (ret)
			return (ret);
		ret = take_blank(&s);
		if (ret != NO_ERROR && ret != INCORRECT_FORMAT)
			return (ret);
		ret = take_eol(&s);
	}
	if (ret)
		return (ret);
	*str = s;
	return (ret);
}

int	take_object(char **str, t_scene *scene)
{
	static int (*const	parsers[])(char **, t_scene *) = {
		take_ambient, take_camera, take_light,
		take_sphere, take_plane, take_cylinder};
	int					ret;
	char				*s;
	t_identifier		identifier;

	s = *str;
	ret = take_identifier(&s, &identifier);
	if (ret)
		return (ret);
	ret = take_blank(&s);
	if (ret)
		return (ret);
	ret = (parsers[identifier])(&s, scene);
	if (ret)
		return (ret);
	*str = s;
	return (NO_ERROR);
}

int	take_eol(char **str)
{
	char	*s;

	s = *str;
	if (!ft_strchr("#\n", *s))
		return (INCORRECT_FORMAT);
	while (*s)
		s++;
	*str = s;
	return (NO_ERROR);
}
