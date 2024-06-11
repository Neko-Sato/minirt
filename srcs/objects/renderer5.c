/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer5.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 20:35:41 by hshimizu          #+#    #+#             */
/*   Updated: 2024/06/11 23:40:09 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects/renderer.h"
#include "rt2img.h"
#include "rt_errno.h"
#include "utils/ray.h"
#include <math.h>
#include <mlx.h>

int	renderer_render(t_renderer *self)
{
	const float		d = ft_deg2rad(self->camera->fov
			/ (float)self->camera->width);
	unsigned int	*img;
	int				i;
	int				j;

	img = (void *)mlx_get_data_addr(self->img, &(int){0}, &(int){0}, &(int){0});
	i = -self->camera->height / 2;
	while (i < self->camera->height / 2)
	{
		j = -self->camera->width / 2;
		while (j < self->camera->width / 2)
		{
			*img++ = rt2img(self->objs,
					(t_ray){matrix3x3_mul_vec3d(self->transform,
						(t_vec3d){{tanf(d * j), -tanf(d * i), 1}}),
					self->camera->coordinates}).raw;
			j++;
		}
		i++;
	}
	mlx_clear_window(self->mlx, self->win);
	mlx_put_image_to_window(self->mlx, self->win, self->img, 0, 0);
	return (NO_ERROR);
}
