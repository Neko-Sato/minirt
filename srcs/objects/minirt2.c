/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 04:30:46 by hshimizu          #+#    #+#             */
/*   Updated: 2024/06/04 02:32:03 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects/minirt.h"
#include "rt_errno.h"
#include <stdlib.h>
#include <unistd.h>

void	__minirt_put_using(void)
{
	ft_putstr_fd(USING, STDERR_FILENO);
}

void	__minirt_show(t_minirt *self)
{
	mlx_loop(self->mlx);
}

int	__minirt_load(char *filename, int width, int height, t_minirt *minirt)
{
	int		ret;
	t_scene	*scene;

	scene = malloc(sizeof(t_scene));
	if (!scene)
		return (FAILED_ALLOCATE);
	ret = g_class_scene.init(scene, filename);
	if (ret)
		return (free(scene), ret);
	ret = g_class_minirt.init(minirt, scene, width, height);
	if (ret)
		return (scene->__class->del(scene), free(scene), ret);
	return (NO_ERROR);
}

void	__minirt_render(t_minirt *self)
{
	(void)self;
}
