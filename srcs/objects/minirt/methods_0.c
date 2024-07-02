/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   methods_0.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 18:15:37 by hshimizu          #+#    #+#             */
/*   Updated: 2024/07/02 22:31:26 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects/minirt.h"
#include "objects/renderer.h"
#include <mlx.h>
#include <stdlib.h>
#include <libft.h>
#include <unistd.h>

t_rt_errno	minirt_loop(t_minirt *self)
{
	ft_putendl_fd("🐈 Welcome to miniRT!", STDOUT_FILENO);
	ft_putstr_fd(KEY_OPERATION_DESCRIPTION, STDOUT_FILENO);
	mlx_loop(self->mlx);
	ft_putendl_fd("🐈 goodbye!", STDOUT_FILENO);
	return (self->errno);
}

static int	loop(t_minirt *self);

void	minirt_set_hook(t_minirt *self)
{
	mlx_do_key_autorepeatoff(self->mlx);
	mlx_loop_hook(self->mlx, loop, self);
}

static int	loop(t_minirt *self)
{
	void		*unnecessary;
	t_xlst		**tmp;
	t_renderer	*renderer;

	tmp = &self->renderers;
	while (*tmp)
	{
		renderer = *(t_renderer **)(*tmp)->data;
		if (!renderer->win)
		{
			unnecessary = *tmp;
			*tmp = (*tmp)->next;
			(void)(renderer_del(renderer), free(renderer), free(unnecessary));
			continue ;
		}
		self->errno = renderer_loop_hook(renderer);
		if (self->errno)
		{
			mlx_loop_end(self->mlx);
			break ;
		}
		tmp = &(*tmp)->next;
	}
	return (0);
}
