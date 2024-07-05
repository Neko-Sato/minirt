/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   methods_3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 18:01:45 by hshimizu          #+#    #+#             */
/*   Updated: 2024/07/05 16:29:45 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects/renderer.h"
#include "objects/scene.h"
#include "rt_errno.h"
#include <mlx.h>

static inline t_rt_errno	trace(t_renderer *self,
		unsigned int *img)
{
	const float	d = self->camera->fov / (float)self->camera->width;
	int			i;
	int			j;
	t_vec3d		tmp;

	i = self->iter / self->box[0];
	while (i < self->camera->height)
	{
		tmp = matrix3x3_mul_vec3d(matrix3x3_rotation_x(d * (i
						- self->camera->height / 2.)), (t_vec3d){{0, 0, 1}});
		j = self->iter % self->box[0];
		while (j < self->camera->width)
		{
			img[i * self->camera->width + j] = scene_trace(self->scene,
					&(t_ray){matrix3x3_mul_vec3d(self->camera->transform,
						matrix3x3_mul_vec3d(matrix3x3_rotation_y(d * (j
									- self->camera->width / 2.)), tmp)),
					self->camera->coord}, self->camera->dist, 1).raw;
			j += self->box[0];
		}
		i += self->box[1];
	}
	return (SUCCESS);
}

static inline t_rt_errno	preview(t_renderer *self,
		unsigned int *img)
{
	const float	d = self->camera->fov / (float)self->camera->width;
	int			i;
	int			j;
	t_vec3d		tmp;

	i = 0;
	while (i < self->camera->height)
	{
		tmp = matrix3x3_mul_vec3d(matrix3x3_rotation_x(d * (i
						- self->camera->height / 2.)), (t_vec3d){{0, 0, 1}});
		j = 0;
		while (j < self->camera->width)
		{
			img[i * self->camera->width + j] = scene_rough_trace(self->scene,
					&(t_ray){matrix3x3_mul_vec3d(self->camera->transform,
						matrix3x3_mul_vec3d(matrix3x3_rotation_y(d * (j
									- self->camera->width / 2.)), tmp)),
					self->camera->coord}, self->camera->dist).raw;
			j += self->preview_box[0];
		}
		i += self->preview_box[1];
	}
	return (SUCCESS);
}

t_rt_errno	renderer_render(t_renderer *self)
{
	t_rt_errno		ret;
	unsigned int	*img;

	img = (void *)mlx_get_data_addr(self->img, &(int){0}, &(int){0}, &(int){0});
	if (self->iter <= 0)
		ft_bzero(img, sizeof(int [self->camera->width][self->camera->height]));
	if (self->iter < 0)
		ret = preview(self, img);
	else
		ret = trace(self, img);
	if (ret)
		return (ret);
	mlx_put_image_to_window(self->mlx, self->win, self->img, 0, 0);
	self->iter++;
	return (SUCCESS);
}
