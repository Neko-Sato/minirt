/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 13:14:54 by hshimizu          #+#    #+#             */
/*   Updated: 2024/05/16 09:50:15 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <libft.h>

int	texture_parser(char *str, t_texture *texture)
{
	char	*tmp;

	if (*str == '(')
	{
		tmp = ft_strchr(str, ')');
		if (tmp)
		{
			str++;
			*tmp++ = '\0';
			return (texture_parser_internal(str, tmp, texture));
		}
	}
	return (t_simple_parser(str, texture));
}

int	texture_parser_internal(char *identifier, char *str, t_texture *texture)
{
	if (!ft_strcmp(IDENTIFIER_T_SIMPLE, identifier))
		return (t_simple_parser(str, texture));
	return (INCORRECT_FORMAT);
}
