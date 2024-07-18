/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   methods_0.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 17:28:35 by hshimizu          #+#    #+#             */
/*   Updated: 2024/07/18 18:21:58 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects/renderer.h"
#include <mlx.h>

void	renderer_destroy_window(t_renderer *self)
{
	if (self->win)
	{
		mlx_destroy_window(self->mlx, self->win);
		self->win = NULL;
	}
}
