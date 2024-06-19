/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_sphere.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 00:30:09 by hshimizu          #+#    #+#             */
/*   Updated: 2024/06/19 16:14:10 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects/sphere.h"
#include "parser.h"
#include "rt_errno.h"
#include <stdlib.h>

static inline int	parse_sphere2(char **str, t_scene *scene, char *s,
						t_sphere *tmp);

int	parse_sphere(char **str, t_scene *scene)
{
	int			ret;
	char		*s;
	t_sphere	*tmp;

	tmp = malloc(sizeof(*tmp));
	if (!tmp)
		return (FAILED_ALLOCATE);
	ret = sphere_init(tmp);
	if (ret)
		return (free(tmp), ret);
	s = *str;
	ret = parse_vec3d(&s, &tmp->coordinates);
	if (ret)
		return (sphere_del(tmp), free(tmp), ret);
	ret = parse_blank(&s);
	if (ret)
		return (sphere_del(tmp), free(tmp), ret);
	ret = parse_decimal(&s, &tmp->diameter, 1);
	if (ret)
		return (sphere_del(tmp), free(tmp), ret);
	ret = parse_blank(&s);
	if (ret)
		return (sphere_del(tmp), free(tmp), ret);
	return (parse_sphere2(str, scene, s, tmp));
}

static inline int	parse_sphere2(char **str, t_scene *scene, char *s,
		t_sphere *tmp)
{
	int	ret;

	ret = parse_color(&s, &((t_figure *)tmp)->color);
	if (ret)
		return (sphere_del(tmp), free(tmp), ret);
	ret = parse_optional(&s, (t_parse_optional_fn)parse_figure_optional, tmp);
	if (ret)
		return (sphere_del(tmp), free(tmp), ret);
	ret = scene_add_figure(scene, (t_figure *)tmp);
	if (ret)
		return (sphere_del(tmp), free(tmp), FAILED_ALLOCATE);
	*str = s;
	return (SUCCESS);
}
