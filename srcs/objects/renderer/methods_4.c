/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   methods_4.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 18:01:45 by hshimizu          #+#    #+#             */
/*   Updated: 2024/07/24 07:48:48 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "constants.h"
#include "objects/renderer.h"
#include "objects/scene.h"
#include "rt_errno.h"
#include "utils/vec3.h"
#include "utils/ray.h"
#include <mlx.h>

static inline t_color	trace(t_renderer *self, t_vec3 tmp,
		int max_depth)
{
	const t_ray	ray = {
		vec3_norm(mat3x3_mul_vec3(self->camera->transform, tmp)),
		self->camera->coord
	};

	return (scene_trace(self->scene, &ray, max_depth));
}

static inline t_rt_errno	renderer_render_internal(t_renderer *self,
		unsigned int *img, const int box[2], int max_depth)
{
	const float	d = self->camera->fov / (float)self->camera->width;
	int			i;
	int			j;
	t_vec3		tmp;

	i = ft_max(0, self->iter) / box[0];
	while (i < self->camera->height)
	{
		tmp = mat3x3_mul_vec3(mat3x3_rotation_x(\
			d * (i - self->camera->height / 2.)), (t_vec3){{0, 0, 1}});
		j = ft_max(0, self->iter) % self->box[0];
		while (j < self->camera->width)
		{
			img[i * self->camera->width + j] = trace(self,
					mat3x3_mul_vec3(mat3x3_rotation_y(\
						d * (j - self->camera->width / 2.)), tmp),
					max_depth).raw;
			j += box[0];
		}
		i += box[1];
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
		ret = renderer_render_internal(self, img, self->preview_box, -1);
	else
		ret = renderer_render_internal(self, img, self->box, MAX_DEPTH);
	if (ret)
		return (ret);
	mlx_put_image_to_window(self->mlx, self->win, self->img, 0, 0);
	self->iter++;
	return (SUCCESS);
}
