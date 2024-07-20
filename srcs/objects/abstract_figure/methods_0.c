/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   methods_0.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 13:15:37 by hshimizu          #+#    #+#             */
/*   Updated: 2024/07/20 04:38:41 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects/abstract_figure.h"
#include "utils/ray.h"
#include <libft.h>

t_color	abstract_figure_get_color(t_abstract_figure *self, const t_vec3d *point)
{
	float	uv[2];

	if (self->_->get_uv_coord && self->checker._.alpha == 0xff)
	{
		self->_->get_uv_coord(self, point, uv);
		if ((int)(uv[0] * 20) % 2 == (int)(uv[1] * 20) % 2)
			return (self->color);
		return (self->checker);
	}
	return (self->color);
}
