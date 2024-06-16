/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer_4.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 14:27:38 by hshimizu          #+#    #+#             */
/*   Updated: 2024/06/16 15:08:05 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects/renderer.h"
#include "rt2img.h"
#include "rt_errno.h"
#include "utils/ray.h"
#include <math.h>
#include <mlx.h>

static inline void	render(t_renderer *self, unsigned int *img)
{
	const float	d = ft_deg2rad(self->camera->fov / (float)self->camera->width);
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
			img[i * self->camera->width
				+ j] = rt2img_test(&(t_ray){matrix3x3_mul_vec3d(self->transform,
						matrix3x3_mul_vec3d(matrix3x3_rotation_y(d * (j
									- self->camera->width / 2.)), tmp)),
					self->camera->coordinates}).raw;
			j++;
		}
		i += self->max_iter;
	}
}

int	renderer_render(t_renderer *self)
{
	unsigned int	*img;

	img = (void *)mlx_get_data_addr(self->img, &(int){0}, &(int){0}, &(int){0});
	if (!self->iter)
		ft_bzero(img, sizeof(int [self->camera->width][self->camera->height]));
	render(self, img);
	mlx_put_image_to_window(self->mlx, self->win, self->img, 0, 0);
	self->iter++;
	return (NO_ERROR);
}
