/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer_0.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 05:31:52 by hshimizu          #+#    #+#             */
/*   Updated: 2024/06/21 23:10:47 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects/renderer.h"
#include "rt2img.h"
#include "rt_errno.h"
#include "utils/ray.h"
#include <math.h>
#include <mlx.h>

int	renderer_init(t_renderer *self, t_renderer_init *args)
{
	*self = (t_renderer){};
	self->mlx = args->mlx;
	self->camera = args->camera;
	self->objs = args->objs;
	self->win = mlx_new_window(self->mlx, self->camera->width,
			self->camera->height, args->title);
	if (!self->win)
		return (FAILED_ALLOCATE);
	self->img = mlx_new_image(self->mlx, self->camera->width,
			self->camera->height);
	if (!self->img)
		return (renderer_del(self), FAILED_ALLOCATE);
	self->max_iter = self->camera->height * self->camera->width
		/ PIXELS_PER_SIDE;
	self->iter = 0;
	self->save = *self->camera;
	renderer_set_hook(self);
	renderer_set_hook2(self);
	mlx_string_put(self->mlx, self->win, self->camera->width / 2,
		self->camera->height / 2, 0xFFFFFF, "now rendering...");
	return (SUCCESS);
}

void	renderer_del(t_renderer *self)
{
	if (self->img)
		mlx_destroy_image(self->mlx, self->img);
	if (self->win)
		mlx_destroy_window(self->mlx, self->win);
}

static inline int	renderer_render_internal(t_renderer *self,
		unsigned int *img)
{
	const float	d = self->camera->fov / (float)self->camera->width;
	int			i;
	int			j;
	t_vec3d		tmp;

	i = self->iter;
	while (i < self->camera->height)
	{
		tmp = matrix3x3_mul_vec3d(matrix3x3_rotation_x(d * (i
						- self->camera->height / 2.)), (t_vec3d){{0, 0, 1}});
		j = 0;
		while (j < self->camera->width)
		{
			img[i * self->camera->width + j] = rt2img(self->objs,
					&(t_ray){matrix3x3_mul_vec3d(self->camera->transform,
						matrix3x3_mul_vec3d(matrix3x3_rotation_y(d * (j
									- self->camera->width / 2.)), tmp)),
					self->camera->coordinates}, 1).raw;
			j++;
		}
		i += self->max_iter;
	}
	return (SUCCESS);
}

int	renderer_render(t_renderer *self)
{
	int				ret;
	unsigned int	*img;

	img = (void *)mlx_get_data_addr(self->img, &(int){0}, &(int){0}, &(int){0});
	if (!self->iter)
		ft_bzero(img, sizeof(int [self->camera->width][self->camera->height]));
	ret = renderer_render_internal(self, img);
	if (ret)
		return (ret);
	mlx_put_image_to_window(self->mlx, self->win, self->img, 0, 0);
	self->iter++;
	return (SUCCESS);
}
