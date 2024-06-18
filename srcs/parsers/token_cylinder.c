/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_cylinder.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 00:58:15 by hshimizu          #+#    #+#             */
/*   Updated: 2024/06/18 19:17:59 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects/cylinder.h"
#include "parser.h"
#include "rt_errno.h"
#include <stdlib.h>

static inline int	parse_cylinder2(char **str, t_scene *scene, char *s,
						t_cylinder *tmp);

int	parse_cylinder(char **str, t_scene *scene)
{
	int			ret;
	char		*s;
	t_cylinder	*tmp;

	tmp = malloc(sizeof(*tmp));
	if (!tmp)
		return (FAILED_ALLOCATE);
	ret = cylinder_init(tmp);
	if (ret)
		return (free(tmp), ret);
	s = *str;
	ret = parse_vec3d(&s, &tmp->coordinates);
	if (ret)
		return (cylinder_del(tmp), free(tmp), ret);
	ret = parse_blank(&s);
	if (ret)
		return (cylinder_del(tmp), free(tmp), ret);
	ret = parse_norm_vec3d(&s, &tmp->axis);
	if (ret)
		return (cylinder_del(tmp), free(tmp), ret);
	if (!tmp->axis._[0] && !tmp->axis._[1] && !tmp->axis._[2])
		return (cylinder_del(tmp), free(tmp), AMBIGUOUS_ORIENTATION);
	return (parse_cylinder2(str, scene, s, tmp));
}

static inline int	parse_cylinder2(char **str, t_scene *scene, char *s,
		t_cylinder *tmp)
{
	int	ret;

	ret = parse_blank(&s);
	if (ret)
		return (cylinder_del(tmp), free(tmp), ret);
	ret = parse_decimal(&s, &tmp->diameter, 1);
	if (ret)
		return (cylinder_del(tmp), free(tmp), ret);
	ret = parse_blank(&s);
	if (ret)
		return (cylinder_del(tmp), free(tmp), ret);
	ret = parse_decimal(&s, &tmp->height, 1);
	if (ret)
		return (cylinder_del(tmp), free(tmp), ret);
	ret = parse_optional(&s, (t_parse_optional_fn)parse_figure_optional, tmp);
	if (ret)
		return (cylinder_del(tmp), free(tmp), ret);
	ret = scene_add_figure(scene, (t_figure *)tmp);
	if (ret)
		return (cylinder_del(tmp), free(tmp), FAILED_ALLOCATE);
	*str = s;
	return (NO_ERROR);
}
