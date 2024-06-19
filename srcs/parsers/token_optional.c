/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_optional.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 04:19:48 by hshimizu          #+#    #+#             */
/*   Updated: 2024/06/19 16:14:10 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "rt_errno.h"
#include "utils/vec3d.h"
#include <libft.h>
#include <limits.h>

int	parse_optional(char **str, t_parse_optional_fn fun, void *value)
{
	int		ret;
	char	*s;

	while (1)
	{
		s = *str;
		ret = parse_blank(&s);
		if (ret == INCORRECT_FORMAT)
			break ;
		if (ret)
			return (ret);
		ret = fun(&s, value);
		if (ret == INCORRECT_FORMAT)
			break ;
		if (ret)
			return (ret);
		*str = s;
	}
	return (SUCCESS);
}

int	parse_figure_optional(char **str, t_figure *value)
{
	int		ret;
	char	*s;
	char	text[20];

	s = *str;
	ret = parse_text(&s, text, sizeof(text));
	if (ret)
		return (ret);
	if (*s++ != '=')
		return (INCORRECT_FORMAT);
	if (!ft_strcmp("reflectivity", text))
		ret = parse_rate(&s, &value->reflectivity);
	else if (!ft_strcmp("checker", text))
		ret = parse_color(&s, &value->checker);
	else if (!ft_strcmp("bump", text))
		ret = parse_string(&s, (char **)&value->bump);
	else
		return (INCORRECT_FORMAT);
	if (ret)
		return (ret);
	*str = s;
	return (SUCCESS);
}

int	parse_camera_optional(char **str, t_camera *value)
{
	int		ret;
	char	*s;
	char	text[10];

	s = *str;
	ret = parse_text(&s, text, sizeof(text));
	if (ret)
		return (ret);
	if (*s++ != '=')
		return (INCORRECT_FORMAT);
	if (!ft_strcmp("width", text))
		ret = parse_integer(&s, &value->width, 1);
	else if (!ft_strcmp("height", text))
		ret = parse_integer(&s, &value->height, 1);
	else if (!ft_strcmp("dist", text))
		ret = parse_decimal(&s, &value->dist, 1);
	else
		return (INCORRECT_FORMAT);
	*str = s;
	return (ret);
}
