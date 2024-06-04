/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_basic_1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 23:47:38 by hshimizu          #+#    #+#             */
/*   Updated: 2024/06/04 02:56:23 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_errno.h"
#include <libft.h>
#include <stddef.h>

static int	take_string_internal(char **str, t_strgen *strgen);

int	take_string(char **str, char **value)
{
	int			ret;
	t_strgen	*strgen;

	strgen = ft_strgennew(STRGEN_BUUFERSIZE);
	if (!strgen)
		return (FAILED_ALLOCATE);
	ret = take_string_internal(str, strgen);
	if (!ret)
	{
		*value = ft_strgencomp(strgen);
		if (!*value)
			ret = FAILED_ALLOCATE;
	}
	ft_strgendel(strgen);
	return (ret);
}

static int	take_string_internal(char **str, t_strgen *strgen)
{
	char	*s;

	s = *str;
	if (*s++ != '"')
		return (INCORRECT_FORMAT);
	while (*s && *s != '"')
	{
		if (*s == '\\')
			if (*++s)
				break ;
		if (ft_strgenchr(strgen, *s++))
			return (FAILED_ALLOCATE);
	}
	if (*s++ != '\"')
		return (INCORRECT_FORMAT);
	*str = s;
	return (NO_ERROR);
}

int	take_text(char **str, char *buf, size_t buf_size)
{
	size_t	len;
	char	*s;

	s = *str;
	len = 0;
	if (ft_isalpha(*s) || *s == '_')
		s++;
	while (ft_isalnum(*s) || *s == '_')
		s++;
	len = s - *str;
	if (len >= buf_size)
		return (UNLIKELY_ERROR);
	ft_strncpy(buf, *str, len);
	buf[len] = '\0';
	*str = s;
	return (NO_ERROR);
}