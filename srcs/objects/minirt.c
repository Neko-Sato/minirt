/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 03:57:27 by hshimizu          #+#    #+#             */
/*   Updated: 2024/06/12 11:53:37 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects/minirt.h"
#include "objects/renderer.h"
#include "objects/scene.h"
#include "rt_errno.h"
#include <mlx.h>
#include <stdlib.h>
#include <unistd.h>

int	minirt_init(t_minirt *self)
{
	*self = (t_minirt){};
	self->mlx = mlx_init();
	if (!self->mlx)
		return (minirt_del(self), FAILED_INITIALIZE_MLX);
	mlx_do_key_autorepeaton(self->mlx);
	mlx_loop_hook(self->mlx, minirt_loop_hook, self);
	return (NO_ERROR);
}

void	minirt_del(t_minirt *self)
{
	void	*tmp;

	while (ft_xlstpop(&self->renderers, 0, &tmp, sizeof(t_renderer *)) != -1)
		(void)(renderer_del((t_renderer *)tmp), free(tmp));
	while (ft_xlstpop(&self->scenes, 0, &tmp, sizeof(t_scene *)) != -1)
		(void)(scene_del((t_scene *)tmp), free(tmp));
	if (self->mlx)
		mlx_destroy_display(self->mlx);
	free(self->mlx);
}

void	minirt_put_using(void)
{
	ft_putstr_fd(USING, STDERR_FILENO);
}

int	minirt_loop(t_minirt *self)
{
	mlx_loop(self->mlx);
	return (self->errno);
}

int	minirt_loop_hook(t_minirt *self)
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
