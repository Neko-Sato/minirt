/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 03:57:27 by hshimizu          #+#    #+#             */
/*   Updated: 2024/07/02 22:29:59 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects/minirt.h"
#include "objects/renderer.h"
#include "objects/scene.h"
#include "rt_errno.h"
#include <mlx.h>
#include <stdlib.h>

t_rt_errno	minirt_init(t_minirt *self, t_minirt_init *args)
{
	(void)args;
	*self = (t_minirt){};
	self->mlx = mlx_init();
	if (!self->mlx)
		return (FAILED_INITIALIZE_MLX);
	minirt_set_hook(self);
	return (SUCCESS);
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
