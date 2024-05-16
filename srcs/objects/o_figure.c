/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   o_figure.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 22:02:57 by hshimizu          #+#    #+#             */
/*   Updated: 2024/05/16 17:14:24 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <libft.h>

int	o_figure_parser(char *str, t_object *object)
{
	t_o_figure *const	figure = &object->value.figure;

	object->type = o_figure;
	return (figure_parser(str, &figure->figure));
}
