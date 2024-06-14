/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer_0.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 05:31:52 by hshimizu          #+#    #+#             */
/*   Updated: 2024/06/14 11:52:38 by hshimizu         ###   ########.fr       */
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
	self->needs_rendring = 1;
	self->camera->orientation = vec3d_norm(self->camera->orientation);
	self->save_ray = (t_ray){self->camera->orientation,
		self->camera->coordinates};
	renderer_update_transform(self);
	renderer_set_hook(self);
	renderer_set_hook2(self);
	mlx_string_put(self->mlx, self->win, self->camera->width / 2,
		self->camera->height / 2, 0xFFFFFF, "now rendering...");
	return (NO_ERROR);
}

void	renderer_del(t_renderer *self)
{
	if (self->img)
		mlx_destroy_image(self->mlx, self->img);
	if (self->win)
		mlx_destroy_window(self->mlx, self->win);
}

void	renderer_update_transform(t_renderer *self)
{
	const t_vec3d		f = vec3d_norm(self->camera->orientation);
	const t_vec3d		r = vec3d_norm(vec3d_cross((t_vec3d){{0, 1, 0}}, f));
	const t_vec3d		u = vec3d_norm(vec3d_cross(f, r));
	const t_matrix3x3	tmp = {{
	{r._[0], u._[0], f._[0]},
	{r._[1], u._[1], f._[1]},
	{r._[2], u._[2], f._[2]},
	}};

	self->transform = tmp;
}

static inline void	render(t_renderer *self, unsigned int *img)
{
	const float	d = ft_deg2rad(self->camera->fov / (float)self->camera->width);
	int			i;
	int			j;
	t_vec3d		tmp;

	i = -self->camera->height / 2;
	while (i < self->camera->height / 2)
	{
		tmp = matrix3x3_mul_vec3d(matrix3x3_rotation_x(d * i), (t_vec3d){{0, 0,
				1}});
		j = -self->camera->width / 2;
		while (j < self->camera->width / 2)
		{
			*img++ = rt2img(self->objs,
					&(t_ray){matrix3x3_mul_vec3d(self->transform,
						matrix3x3_mul_vec3d(matrix3x3_rotation_y(d * j), tmp)),
					self->camera->coordinates}).raw;
			j++;
		}
		i++;
	}
}

int	renderer_render(t_renderer *self)
{
	unsigned int	*img;

	img = (void *)mlx_get_data_addr(self->img, &(int){0}, &(int){0}, &(int){0});
	render(self, img);
	mlx_clear_window(self->mlx, self->win);
	mlx_put_image_to_window(self->mlx, self->win, self->img, 0, 0);
	return (NO_ERROR);
}
