/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 20:21:46 by hshimizu          #+#    #+#             */
/*   Updated: 2024/07/13 19:12:51 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "rt_errno.h"

t_rt_errno	parse_blank(char **str)
{
	char	*s;

	s = *str;
	while (ft_isblank(*s))
		s++;
	if (*str == s)
		return (INCORRECT_FORMAT);
	*str = s;
	return (SUCCESS);
}

t_rt_errno	parse_text(char **str, char *buf, size_t size)
{
	size_t	len;
	char	*s;

	s = *str;
	if (ft_isalpha(*s) || *s == '_')
	{
		s++;
		while (ft_isalnum(*s) || *s == '_')
			s++;
	}
	len = s - *str;
	if (!len || len >= size)
		return (INCORRECT_FORMAT);
	ft_strncpy(buf, *str, len);
	buf[len] = '\0';
	*str = s;
	return (SUCCESS);
}

t_rt_errno	parse_entries(char **str, const t_parse_entry *entries, size_t size)
{
	t_rt_errno	ret;
	char		*s;
	size_t		i;

	ret = SUCCESS;
	s = *str;
	i = 0;
	while (1)
	{
		ret = entries[i].fun(&s, entries[i].dst);
		if (ret)
			return (ret);
		i++;
		if (size <= i)
			break ;
		ret = parse_blank(&s);
		if (ret)
			return (ret);
	}
	*str = s;
	return (ret);
}

static t_rt_errno	parse_optional_internal(char **str,
				const t_parse_opt *entries, size_t size);

t_rt_errno	parse_optional(char **str, const t_parse_opt *entries, size_t size)
{
	t_rt_errno	ret;
	char		*s;

	s = *str;
	while (1)
	{
		ret = parse_blank(&s);
		if (ret == INCORRECT_FORMAT)
			break ;
		if (ret)
			return (ret);
		ret = parse_optional_internal(&s, entries, size);
		if (ret == INCORRECT_FORMAT)
			break ;
		if (ret)
			return (ret);
	}
	*str = s;
	return (SUCCESS);
}

static t_rt_errno	parse_optional_internal(char **str,
		const t_parse_opt *entries, size_t size)
{
	t_rt_errno	ret;
	char		*s;
	char		buf[20];
	size_t		i;

	s = *str;
	ret = parse_text(&s, buf, sizeof(buf));
	if (ret)
		return (ret);
	if (*s++ != '=')
		return (INCORRECT_FORMAT);
	i = 0;
	while (i < size && ft_strcmp(entries[i].name, buf))
		i++;
	if (size <= i)
		return (INCORRECT_FORMAT);
	ret = entries[i].fun(&s, entries[i].dst);
	if (ret)
		return (ret);
	*str = s;
	return (SUCCESS);
}
