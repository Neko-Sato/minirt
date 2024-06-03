/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_basic_0.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 23:47:38 by hshimizu          #+#    #+#             */
/*   Updated: 2024/06/04 00:53:09 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "rt_errno.h"
#include <libft.h>
#include <stddef.h>

int	take_blank(char **str)
{
	char	*s;

	s = *str;
	while (ft_isblank(*s))
		s++;
	if (*str == s)
		return (INCORRECT_FORMAT);
	*str = s;
	return (NO_ERROR);
}

int	take_identifier(char **str, t_identifier *value)
{
	static const char *const	identifiers[] = {
		"A", "C", "L", "sp", "pl", "cy"};
	int							i;
	size_t						len;

	i = 0;
	while (i < IDENTIFIER_NUM)
	{
		len = ft_strlen(identifiers[i]);
		if (!ft_strncmp(*str, identifiers[i], len))
			break ;
		i++;
	}
	if (i >= IDENTIFIER_NUM)
		return (UNKNOW_IDENTIFIER);
	*str += len;
	*value = i;
	return (NO_ERROR);
}

int	take_integer(char **str, long *value)
{
	char	*endptr;

	*value = ft_strtol(*str, &endptr, 10);
	if (endptr == *str)
		return (INCORRECT_FORMAT);
	*str = endptr;
	return (NO_ERROR);
}

int	take_decimal(char **str, double *value)
{
	char	*endptr;

	*value = ft_strtod(*str, &endptr);
	if (endptr == *str)
		return (INCORRECT_FORMAT);
	*str = endptr;
	return (NO_ERROR);
}
