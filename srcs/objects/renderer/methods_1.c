/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   methods_1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 18:28:48 by hshimizu          #+#    #+#             */
/*   Updated: 2024/07/18 17:33:50 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects/renderer.h"
#include <X11/X.h>
#include <mlx.h>

static int	destroy(t_renderer *self);
static int	expose_hook(t_renderer *self);
static int	focusin_hook(t_renderer *self);
static int	focusout_hook(t_renderer *self);

void	renderer_set_hook(t_renderer *self)
{
	mlx_hook(self->win, DestroyNotify, StructureNotifyMask, destroy,
		self);
	mlx_hook(self->win, Expose, ExposureMask, expose_hook, self);
	mlx_hook(self->win, FocusIn, FocusChangeMask, focusin_hook, self);
	mlx_hook(self->win, FocusOut, FocusChangeMask, focusout_hook, self);
}

static int	destroy(t_renderer *self)
{
	renderer_destroy_window(self);
	return (0);
}

static int	expose_hook(t_renderer *self)
{
	self->iter = 0;
	return (0);
}

static int	focusin_hook(t_renderer *self)
{
	self->focus = 1;
	return (0);
}

static int	focusout_hook(t_renderer *self)
{
	self->focus = 0;
	self->action = (t_action){0};
	return (0);
}
