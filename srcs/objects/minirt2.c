/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 04:30:46 by hshimizu          #+#    #+#             */
/*   Updated: 2024/06/05 00:23:44 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects/minirt.h"
#include "rt_errno.h"
#include <stdlib.h>
#include <unistd.h>

void	minirt_put_using(void)
{
	ft_putstr_fd(USING, STDERR_FILENO);
}

void	minirt_show(t_minirt *self)
{
	mlx_loop(self->mlx);
}

int	minirt_load(char *filename, int width, int height, t_minirt *minirt)
{
	int		ret;
	t_scene	*scene;

	scene = malloc(sizeof(t_scene));
	if (!scene)
		return (FAILED_ALLOCATE);
	ret = scene_init(scene, filename);
	if (ret)
		return (free(scene), ret);
	ret = minirt_init(minirt, scene, width, height);
	if (ret)
		return (scene_del(scene), free(scene), ret);
	return (NO_ERROR);
}

void	minirt_render(t_minirt *self)
{
	void *data;

	data = mlx_get_data_addr(self->img, &(int){0}, &(int){0}, &(int){0});
	scene_drawing(self->scene, data, self->width, self->height);
	mlx_put_image_to_window(self->mlx, self->win, self->img, 0, 0);
}