/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 04:30:46 by hshimizu          #+#    #+#             */
/*   Updated: 2024/06/05 10:46:00 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects/minirt.h"
#include "rt2img.h"
#include "rt_errno.h"
#include <stdlib.h>
#include <unistd.h>

void	minirt_del(t_minirt *self)
{
	if (self->img)
		mlx_destroy_image(self->mlx, self->img);
	if (self->win)
		mlx_destroy_window(self->mlx, self->win);
	if (self->mlx)
		mlx_destroy_display(self->mlx);
	free(self->mlx);
	if (self->scene)
		scene_del(self->scene);
	free(self->scene);
}

void	minirt_put_using(void)
{
	ft_putstr_fd(USING, STDERR_FILENO);
}

int	minirt_show(t_minirt *self)
{
	mlx_string_put(self->mlx, self->win, self->scene->camera->width / 2,
		self->scene->camera->height / 2, 0xFFFFFF, "now rendering...");
	self->errno = NO_ERROR;
	mlx_loop(self->mlx);
	return (self->errno);
}

int	minirt_render(t_minirt *self)
{
	int		ret;
	void	*data;

	data = mlx_get_data_addr(self->img, &(int){0}, &(int){0}, &(int){0});
	ret = rt2img(self->scene, data);
	if (ret)
		return (ret);
	mlx_put_image_to_window(self->mlx, self->win, self->img, 0, 0);
	return (NO_ERROR);
}
