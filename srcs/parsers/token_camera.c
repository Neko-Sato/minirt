/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_camera.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 00:17:18 by hshimizu          #+#    #+#             */
/*   Updated: 2024/06/05 00:03:06 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects/camera.h"
#include "parser.h"
#include "rt_errno.h"
#include "utils/vec3d.h"
#include <stdlib.h>

static inline int	take_camera2(char **str, t_scene *scene, char *s,
						t_camera *tmp);

int	take_camera(char **str, t_scene *scene)
{
	int			ret;
	char		*s;
	t_camera	*tmp;

	tmp = malloc(sizeof(*tmp));
	if (!tmp)
		return (FAILED_ALLOCATE);
	ret = camera_init(tmp);
	if (ret)
		return (free(tmp), ret);
	s = *str;
	ret = take_vec3d(&s, &tmp->coordinates);
	if (ret)
		return (camera_del(tmp), free(tmp), ret);
	ret = take_blank(&s);
	if (ret)
		return (camera_del(tmp), free(tmp), ret);
	ret = take_norm_vec3d(&s, &tmp->orientation);
	if (ret)
		return (camera_del(tmp), free(tmp), ret);
	ret = take_blank(&s);
	if (ret)
		return (camera_del(tmp), free(tmp), ret);
	return (take_camera2(str, scene, s, tmp));
}

static inline int	take_camera2(char **str, t_scene *scene, char *s,
		t_camera *tmp)
{
	int		ret;
	long	fov;

	ret = take_integer(&s, &fov);
	if (ret)
		return (camera_del(tmp), free(tmp), ret);
	if (fov < 0 || fov > 180)
		return (camera_del(tmp), free(tmp), INCORRECT_FORMAT);
	tmp->fov = fov;
	ret = scene_set_camera(scene, tmp);
	if (ret)
		return (camera_del(tmp), free(tmp), FAILED_ALLOCATE);
	*str = s;
	return (NO_ERROR);
}
