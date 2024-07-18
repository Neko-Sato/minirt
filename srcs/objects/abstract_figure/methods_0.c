/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   methods_0.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 13:15:37 by hshimizu          #+#    #+#             */
/*   Updated: 2024/07/19 00:04:47 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects/abstract_figure.h"
#include "utils/ray.h"
#include <libft.h>

t_color	abstract_figure_get_color(t_abstract_figure *self, const t_ray *normal)
{
	(void)normal;
	return (self->color);
}
