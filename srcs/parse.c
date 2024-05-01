/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 07:27:42 by hshimizu          #+#    #+#             */
/*   Updated: 2024/05/02 06:12:02 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects.h"
#include <libft.h>

static int	parse_internal(char *str, t_objstype type, t_object *object);

int	parse(char *str, t_object *object)
{
	char	*token;
	size_t	i;

	token = ft_strsep(&str, " \n");
	if (!token)
	{
		object->type = o_none;
		return (0);
	}
	i = 0;
	while (i < g_object_num)
	{
		if (!ft_strcmp(g_parse_objects[i]->identifier, token))
			break ;
		i++;
	}
	if (g_object_num <= i)
		return (-1);
	return (parse_internal(str, i, object));
}

static int	parse_internal(char *str, t_objstype type, t_object *object)
{
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
		{
			if (i < parse->required)
				return (-1);
			break ;
		}
		if (parse->entry[i].parse_fun(token, (unsigned char *)&object->value
				+ parse->entry[i].dst_offset))
			return (-1);
		i++;
	}
	return (0);
}
