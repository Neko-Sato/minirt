/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_plane.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 00:30:09 by hshimizu          #+#    #+#             */
/*   Updated: 2024/06/04 00:37:59 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects/plane.h"
#include "parser.h"
#include "rt_errno.h"
#include <stdlib.h>

static inline int	take_plane2(char **str, t_scene *scene, char *s,
						t_plane *tmp);

int	take_plane(char **str, t_scene *scene)
{
	int		ret;
	char	*s;
	t_plane	*tmp;

	tmp = malloc(sizeof(*tmp));
	if (!tmp)
		return (FAILED_ALLOCATE);
	ret = plane_init(tmp);
	if (ret)
		return (free(tmp), ret);
	s = *str;
	ret = take_vec3d(&s, &((t_figure *)tmp)->coordinates);
	if (ret)
		return (plane_del(tmp), free(tmp), ret);
	ret = take_blank(&s);
	if (ret)
		return (plane_del(tmp), free(tmp), ret);
	ret = take_norm_vec3d(&s, &tmp->normal);
	if (ret)
		return (plane_del(tmp), free(tmp), ret);
	ret = take_blank(&s);
	if (ret)
		return (plane_del(tmp), free(tmp), ret);
	return (take_plane2(str, scene, s, tmp));
}

static inline int	take_plane2(char **str, t_scene *scene, char *s,
		t_plane *tmp)
{
	int	ret;

	ret = take_color(&s, &((t_figure *)tmp)->color);
	if (ret)
		return (plane_del(tmp), free(tmp), ret);
	ret = take_optional(&s, (t_take_optional_fn)take_figure_optional, tmp);
	if (ret)
		return (plane_del(tmp), free(tmp), ret);
	ret = scene_add_figure(scene, (t_figure *)tmp);
	if (ret)
		return (plane_del(tmp), free(tmp), FAILED_ALLOCATE);
	*str = s;
	return (NO_ERROR);
}
