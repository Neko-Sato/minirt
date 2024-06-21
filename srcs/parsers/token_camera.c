/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_camera.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 00:17:18 by hshimizu          #+#    #+#             */
/*   Updated: 2024/06/22 00:04:20 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects/camera.h"
#include "objects/minirt.h"
#include "parser.h"
#include "rt_errno.h"
#include "utils/vec3d.h"
#include <stdlib.h>
#include <math.h>

static inline int	parse_camera2(char **str, t_scene *scene, char *s,
						t_camera *tmp);

int	parse_camera(char **str, t_scene *scene)
{
	int			ret;
	char		*s;
	t_camera	*tmp;
	t_vec3d		orientation;

	tmp = malloc(sizeof(*tmp));
	if (!tmp)
		return (FAILED_ALLOCATE);
	ret = camera_init(tmp);
	if (ret)
		return (free(tmp), ret);
	s = *str;
	ret = parse_vec3d(&s, &tmp->coordinates);
	if (ret)
		return (camera_del(tmp), free(tmp), ret);
	ret = parse_blank(&s);
	if (ret)
		return (camera_del(tmp), free(tmp), ret);
	ret = parse_vec3d(&s, &orientation);
	if (ret)
		return (camera_del(tmp), free(tmp), ret);
	ret = camera_transform(orientation, (t_vec3d){{0, 1, 0}}, &tmp->transform);
	if (ret)
		return (camera_del(tmp), free(tmp), ret);
	return (parse_camera2(str, scene, s, tmp));
}

static inline int	parse_camera2(char **str, t_scene *scene, char *s,
		t_camera *tmp)
{
	int		fov;
	int		ret;

	ret = parse_blank(&s);
	if (ret)
		return (camera_del(tmp), free(tmp), ret);
	ret = parse_integer(&s, &fov, 1);
	if (ret)
		return (camera_del(tmp), free(tmp), ret);
	if (!ALLOW_FOV_UNLIMITED && fov > 180)
		return (camera_del(tmp), free(tmp), OUT_OF_RANGE);
	tmp->fov = ft_deg2rad(fov);
	ret = parse_optional(&s, (t_parse_optional_fn)parse_camera_optional, tmp);
	if (ret)
		return (camera_del(tmp), free(tmp), ret);
	ret = scene_add_camera(scene, tmp);
	if (ret)
		return (camera_del(tmp), free(tmp), FAILED_ALLOCATE);
	*str = s;
	return (SUCCESS);
}
