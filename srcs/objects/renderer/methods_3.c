/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   methods_3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 18:01:45 by hshimizu          #+#    #+#             */
/*   Updated: 2024/07/14 05:23:24 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects/renderer.h"
#include "objects/scene.h"
#include "rt_errno.h"
#include "constants.h"
#include <mlx.h>

static inline t_color	trace(t_scene *scene, const t_ray *ray)
{
	return (scene_trace(scene, ray, MAX_DIST, MAX_DEPTH));
}

static inline t_color	preview(t_scene *scene, const t_ray *ray)
{
	return (scene_rough_trace(scene, ray, MAX_DIST));
}

static inline t_rt_errno	renderer_render_internal(\
	t_renderer *self, unsigned int *img, const int box[2], \
	t_color (*trace)(t_scene *scene, const t_ray *ray))
{
	const float	d = self->camera->fov / (float)self->camera->width;
	int			i;
	int			j;
	t_vec3d		tmp;

	i = ft_max(0, self->iter) / box[0];
	while (i < self->camera->height)
	{
		tmp = matrix3x3_mul_vec3d(matrix3x3_rotation_x(d * (i
						- self->camera->height / 2.)), (t_vec3d){{0, 0, 1}});
		j = ft_max(0, self->iter) % self->box[0];
		while (j < self->camera->width)
		{
			img[i * self->camera->width + j] = trace(self->scene,
					&(t_ray){
					vec3d_norm(matrix3x3_mul_vec3d(self->camera->transform, \
					matrix3x3_mul_vec3d(matrix3x3_rotation_y(\
					d * (j - self->camera->width / 2.)), tmp))),
					self->camera->coord
				}).raw;
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
		ret = renderer_render_internal(self, img, self->preview_box, preview);
	else
		ret = renderer_render_internal(self, img, self->box, trace);
	if (ret)
		return (ret);
	mlx_put_image_to_window(self->mlx, self->win, self->img, 0, 0);
	self->iter++;
	return (SUCCESS);
}
