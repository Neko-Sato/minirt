/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_camera.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 00:17:18 by hshimizu          #+#    #+#             */
/*   Updated: 2024/06/19 16:14:10 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects/camera.h"
#include "parser.h"
#include "rt_errno.h"
#include "utils/vec3d.h"
#include <stdlib.h>

static inline int	parse_camera2(char **str, t_scene *scene, char *s,
						t_camera *tmp);

int	parse_camera(char **str, t_scene *scene)
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
	ret = parse_vec3d(&s, &tmp->coordinates);
	if (ret)
		return (camera_del(tmp), free(tmp), ret);
	ret = parse_blank(&s);
	if (ret)
		return (camera_del(tmp), free(tmp), ret);
	return (parse_camera2(str, scene, s, tmp));
}

static inline int	parse_camera2(char **str, t_scene *scene, char *s,
		t_camera *tmp)
{
	int	ret;

	ret = parse_vec3d(&s, &tmp->orientation);
	if (ret)
		return (camera_del(tmp), free(tmp), ret);
	if (!tmp->orientation._[0] && !tmp->orientation._[2])
		return (camera_del(tmp), free(tmp), AMBIGUOUS_ORIENTATION);
	ret = parse_blank(&s);
	if (ret)
		return (camera_del(tmp), free(tmp), ret);
	ret = parse_integer(&s, &tmp->fov, 1);
	if (ret)
		return (camera_del(tmp), free(tmp), ret);
	if (!ALLOW_FOV_UNLIMITED && tmp->fov > 180)
		return (camera_del(tmp), free(tmp), OUT_OF_RANGE);
	ret = parse_optional(&s, (t_parse_optional_fn)parse_camera_optional, tmp);
	if (ret)
		return (camera_del(tmp), free(tmp), ret);
	ret = scene_add_camera(scene, tmp);
	if (ret)
		return (camera_del(tmp), free(tmp), FAILED_ALLOCATE);
	*str = s;
	return (SUCCESS);
}
