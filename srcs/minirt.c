/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 02:45:29 by hshimizu          #+#    #+#             */
/*   Updated: 2024/05/16 17:06:05 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <X11/X.h>
#include <X11/keysym.h>
#include <libft.h>
#include <mlx.h>
#include <stdlib.h>

static int	rt_loop(t_minirt *rt);
static int	rt_key_hook(int keycode, t_minirt *rt);

int	new_rt(t_minirt *rt, int size[2], char *filename)
{
	int	ret;

	*rt = (t_minirt){};
	rt->mlx = mlx_init();
	if (!rt->mlx)
		return (FAILED_INITIALIZE_MLX);
	ret = load_rt(&rt->scene, filename);
	if (ret)
		return (del_rt(rt), ret);
	rt->win = mlx_new_window(rt->mlx, size[0], size[1], rt->scene.title);
	if (!rt->win)
		return (del_rt(rt), FAILED_ALLOCATE);
	rt->img = mlx_new_image(rt->mlx, size[0], size[1]);
	if (!rt->img)
		return (del_rt(rt), FAILED_ALLOCATE);
	mlx_hook(rt->win, DestroyNotify, NoEventMask, mlx_loop_end, rt->mlx);
	mlx_key_hook(rt->win, rt_key_hook, rt);
	mlx_loop_hook(rt->mlx, rt_loop, (void *)rt);
	ft_memcpy(rt->size, size, sizeof(rt->size));
	rt->needs_rendering = 1;
	return (NO_ERROR);
}

void	del_rt(t_minirt *rt)
{
	if (rt->img)
		mlx_destroy_image(rt->mlx, rt->img);
	if (rt->win)
		mlx_destroy_window(rt->mlx, rt->win);
	if (rt->mlx)
		mlx_destroy_display(rt->mlx);
	free(rt->mlx);
	scene_del(&rt->scene);
	*rt = (t_minirt){};
}

static int	rt_loop(t_minirt *rt)
{
	if (rt->needs_rendering)
	{
		rt->needs_rendering = 0;
		rt2img(&rt->scene, (void *)mlx_get_data_addr(rt->img, &(int){0},
				&(int){0}, &(int){0}), rt->size);
		mlx_clear_window(rt->mlx, rt->win);
		mlx_put_image_to_window(rt->mlx, rt->win, rt->img, 0, 0);
	}
	return (0);
}

static int	rt_key_hook(int keycode, t_minirt *rt)
{
	if (keycode == XK_Escape)
		mlx_loop_end(rt->mlx);
	return (0);
}

int	show_rt(t_minirt *rt)
{
	mlx_string_put(rt->mlx, rt->win, rt->size[0] / 2, rt->size[1] / 2,
		COLOR_RAW_WHITE, "now rendering....");
	mlx_loop(rt->mlx);
	return (0);
}
