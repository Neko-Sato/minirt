/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 07:27:42 by hshimizu          #+#    #+#             */
/*   Updated: 2024/05/08 19:49:41 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects.h"
#include "rt_error.h"
#include <libft.h>

static int	parse_internal(char *str, t_objstype type, t_object *object);

int	parse(char *str, t_object *object)
{
	char	*token;
	size_t	i;

	token = ft_strsep(&str, " \n");
	if (!token || !ft_strncmp(token, "#", 1))
	{
		object->type = o_none;
		return (NO_ERROR);
	}
	i = 0;
	while (i < g_object_num)
	{
		if (!ft_strcmp(g_parse_objects[i]->identifier, token))
			break ;
		i++;
	}
	if (g_object_num <= i)
		return (UNKNOW_IDENTIFIER);
	return (parse_internal(str, i, object));
}

static int	parse_internal(char *str, t_objstype type, t_object *object)
{
	int				ret;
	const t_parse	*parse;
	char			*token;
	size_t			i;

	object->type = type;
	parse = g_parse_objects[type];
	i = 0;
	while (i < parse->size)
	{
		token = ft_strsep(&str, " \n");
		if (!token)
			break ;
		ret = parse->entry[i].parse_fun(token, (unsigned char *)&object->value
				+ parse->entry[i].dst_offset);
		if (ret)
			return (ret);
		i++;
	}
	return (NO_ERROR);
}
