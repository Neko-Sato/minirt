/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   methods_0.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 13:15:37 by hshimizu          #+#    #+#             */
/*   Updated: 2024/07/24 12:08:13 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects/abstract_figure.h"
#include "utils/ray.h"
#include <libft.h>
#include <math.h>

t_color	abstract_figure_get_color(t_abstract_figure *self, const t_vec3 *point)
{
	float	uv[2];

	self->_->get_uv_coord(self, point, uv);
	uv[0] -= floor(uv[0]);
	uv[1] -= floor(uv[1]);
	if ((int)(uv[0] * 20) % 2 == (int)(uv[1] * 20) % 2)
		return (ft_hsvt(uv[0] - floor(uv[0]), uv[1] - floor(uv[1]), 1, 1));
	return (self->color);
}
