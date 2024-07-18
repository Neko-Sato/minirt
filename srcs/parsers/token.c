/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 19:23:41 by hshimizu          #+#    #+#             */
/*   Updated: 2024/07/17 20:03:28 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "rt_errno.h"
#include <libft.h>

t_rt_errno	parse_line(char **str, t_parser *context)
{
	t_rt_errno	ret;
	char		*s;

	s = *str;
	ret = parse_blank(&s);
	if (ret != SUCCESS && ret != INCORRECT_FORMAT)
		return (ret);
	ret = parse_eol(&s);
	if (ret == INCORRECT_FORMAT)
	{
		ret = parse_object(&s, context);
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

t_rt_errno	parse_eol(char **str)
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

t_rt_errno	parse_object(char **str, t_parser *context)
{
	t_rt_errno			ret;
	char				*s;
	const t_identifier	*identifier;

	s = *str;
	ret = parse_identifier(&s, &identifier);
	if (ret)
		return (ret);
	ret = identifier->fun(&s, context);
	if (ret)
		return (ret);
	*str = s;
	return (SUCCESS);
}

const t_identifier	g_identifiers[] = {
{"A", (void *)parse_ambient},
{"C", (void *)parse_camera},
{"L", (void *)parse_light},
{"sp", (void *)parse_sphere},
{"pl", (void *)parse_plane},
{"cy", (void *)parse_cylinder},
{"tr", (void *)parse_triangle},
{"cn", (void *)parse_cone},
};

const size_t		g_identifiers_size = \
	sizeof(g_identifiers) / sizeof(*g_identifiers);

t_rt_errno	parse_identifier(char **str, const t_identifier **identifier)
{
	t_rt_errno	ret;
	char		*s;
	char		buf[3];
	size_t		i;

	s = *str;
	ret = parse_text(&s, buf, sizeof(buf));
	if (ret)
		return (ret);
	i = 0;
	while (i < g_identifiers_size)
	{
		if (!ft_strcmp(g_identifiers[i].name, buf))
			break ;
		i++;
	}
	if (g_identifiers_size <= i)
		return (UNKNOW_IDENTIFIER);
	ret = parse_blank(&s);
	if (ret)
		return (ret);
	*identifier = &g_identifiers[i];
	*str = s;
	return (SUCCESS);
}
