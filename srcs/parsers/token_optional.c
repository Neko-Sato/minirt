/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_optional.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 04:19:48 by hshimizu          #+#    #+#             */
/*   Updated: 2024/06/08 04:45:03 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "rt_errno.h"
#include "utils/vec3d.h"
#include <limits.h>
#include <libft.h>

int	take_optional(char **str, t_take_optional_fn fun, void *value)
{
	int		ret;
	char	*s;

	while (1)
	{
		s = *str;
		ret = take_blank(&s);
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
	return (NO_ERROR);
}

int	take_figure_optional(char **str, t_figure *value)
{
	int		ret;
	char	*s;
	char	text[20];

	s = *str;
	ret = take_text(&s, text, sizeof(text));
	if (ret)
		return (ret);
	if (*s++ != '=')
		return (INCORRECT_FORMAT);
	if (!ft_strcmp("reflectivity", text))
		ret = take_rate(&s, &value->reflectivity);
	else if (!ft_strcmp("checker", text))
		ret = take_color(&s, &value->checker);
	else if (!ft_strcmp("bump", text))
		ret = take_string(&s, (char **)&value->bump);
	else
		return (INCORRECT_FORMAT);
	if (ret)
		return (ret);
	*str = s;
	return (NO_ERROR);
}

static int	take_size(char **str, int *value)
{
	int		ret;
	char	*s;

	s = *str;
	ret = take_integer(&s, value);
	if (ret)
		return (ret);
	if (*value <= 0)
		return (INCORRECT_FORMAT);
	*str = s;
	return (NO_ERROR);
}

int	take_camera_optional(char **str, t_camera *value)
{
	int		ret;
	char	*s;
	char	text[10];

	s = *str;
	ret = take_text(&s, text, sizeof(text));
	if (ret)
		return (ret);
	if (*s++ != '=')
		return (INCORRECT_FORMAT);
	if (!ft_strcmp("width", text))
		ret = take_size(&s, &value->width);
	else if (!ft_strcmp("height", text))
		ret = take_size(&s, &value->height);
	else
		return (INCORRECT_FORMAT);
	*str = s;
	return (NO_ERROR);
}
