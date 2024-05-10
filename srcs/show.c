/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 16:12:52 by hshimizu          #+#    #+#             */
/*   Updated: 2024/05/03 22:59:16 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "rt_error.h"
#include <X11/X.h>
#include <X11/keysym.h>
#include <mlx.h>

static int			keyevent(int keycode, void *mlx);
static unsigned int	*get_img_data_addr(void *img);

void	*show_rt(t_minirt *rt, void *mlx, char *title, int size[2])
{
	void	*win;
	void	*img;

	img = mlx_new_image(mlx, size[0], size[1]);
	if (!img)
		return (NULL);
	rt2img(rt, size, get_img_data_addr(img));
	win = mlx_new_window(mlx, size[0], size[1], title);
	if (win)
	{
		mlx_put_image_to_window(mlx, win, img, 0, 0);
		mlx_key_hook(win, keyevent, mlx);
		mlx_hook(win, DestroyNotify, NoEventMask, mlx_loop_end, mlx);
	}
	mlx_destroy_image(mlx, img);
	return (win);
}

static unsigned int	*get_img_data_addr(void *img)
{
	int	bits_per_pixel;
	int	size_line;
	int	endian;

	return ((unsigned int *)mlx_get_data_addr(img, &bits_per_pixel, &size_line,
			&endian));
}

static int	keyevent(int keycode, void *mlx)
{
	if (keycode == XK_Escape)
		mlx_loop_end(mlx);
	return (0);
}
