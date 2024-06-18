/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_triangle.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 00:30:09 by hshimizu          #+#    #+#             */
/*   Updated: 2024/06/18 19:45:27 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects/triangle.h"
#include "parser.h"
#include "rt_errno.h"
#include <stdlib.h>

static inline int	parse_triangle2(char **str, t_scene *scene, char *s,
						t_triangle *tmp);

int	parse_triangle(char **str, t_scene *scene)
{
	int			ret;
	char		*s;
	t_triangle	*tmp;

	tmp = malloc(sizeof(*tmp));
	if (!tmp)
		return (FAILED_ALLOCATE);
	ret = triangle_init(tmp);
	if (ret)
		return (free(tmp), ret);
	s = *str;
	ret = parse_vec3d(&s, &tmp->first);
	if (ret)
		return (triangle_del(tmp), free(tmp), ret);
	ret = parse_blank(&s);
	if (ret)
		return (triangle_del(tmp), free(tmp), ret);
	ret = parse_vec3d(&s, &tmp->second);
	if (ret)
		return (triangle_del(tmp), free(tmp), ret);
	ret = parse_blank(&s);
	if (ret)
		return (triangle_del(tmp), free(tmp), ret);
	return (parse_triangle2(str, scene, s, tmp));
}

static inline int	parse_triangle2(char **str, t_scene *scene, char *s,
		t_triangle *tmp)
{
	int	ret;

	ret = parse_vec3d(&s, &tmp->third);
	if (ret)
		return (triangle_del(tmp), free(tmp), ret);
	ret = parse_blank(&s);
	if (ret)
		return (triangle_del(tmp), free(tmp), ret);
	ret = parse_color(&s, &((t_figure *)tmp)->color);
	if (ret)
		return (triangle_del(tmp), free(tmp), ret);
	ret = parse_optional(&s, (t_parse_optional_fn)parse_figure_optional, tmp);
	if (ret)
		return (triangle_del(tmp), free(tmp), ret);
	ret = scene_add_figure(scene, (t_figure *)tmp);
	if (ret)
		return (triangle_del(tmp), free(tmp), FAILED_ALLOCATE);
	*str = s;
	return (NO_ERROR);
}
