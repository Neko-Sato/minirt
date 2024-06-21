/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_plane.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 00:30:09 by hshimizu          #+#    #+#             */
/*   Updated: 2024/06/22 01:20:14 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects/plane.h"
#include "parser.h"
#include "rt_errno.h"
#include <math.h>
#include <stdlib.h>

/*
	There are no vertices because there are no edges,
	unlike with a rectangle. It is uniquely defined,
	so there is no ambiguous orientation.
*/

static inline int	parse_plane2(char **str, t_scene *scene, char *s,
						t_plane *tmp);

int	parse_plane(char **str, t_scene *scene)
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
	ret = parse_vec3d(&s, &tmp->coordinates);
	if (ret)
		return (plane_del(tmp), free(tmp), ret);
	ret = parse_blank(&s);
	if (ret)
		return (plane_del(tmp), free(tmp), ret);
	ret = parse_norm_vec3d(&s, &tmp->orientation);
	if (!vec3d_abs(tmp->orientation))
		return (plane_del(tmp), free(tmp), AMBIGUOUS_ORIENTATION);
	if (ret)
		return (plane_del(tmp), free(tmp), ret);
	return (parse_plane2(str, scene, s, tmp));
}

static inline int	parse_plane2(char **str, t_scene *scene, char *s,
		t_plane *tmp)
{
	int	ret;

	ret = parse_blank(&s);
	if (ret)
		return (plane_del(tmp), free(tmp), ret);
	ret = parse_color(&s, &((t_figure *)tmp)->color);
	if (ret)
		return (plane_del(tmp), free(tmp), ret);
	ret = parse_optional(&s, (t_parse_optional_fn)parse_figure_optional, tmp);
	if (ret)
		return (plane_del(tmp), free(tmp), ret);
	ret = scene_add_figure(scene, (t_figure *)tmp);
	if (ret)
		return (plane_del(tmp), free(tmp), FAILED_ALLOCATE);
	*str = s;
	return (SUCCESS);
}
