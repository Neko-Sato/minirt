/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_cylinder.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 00:58:15 by hshimizu          #+#    #+#             */
/*   Updated: 2024/06/04 00:58:17 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects/cylinder.h"
#include "parser.h"
#include "rt_errno.h"
#include <stdlib.h>

static inline int	take_cylinder2(char **str, t_scene *scene, char *s,
						t_cylinder *tmp);

int	take_cylinder(char **str, t_scene *scene)
{
	int			ret;
	char		*s;
	t_cylinder	*tmp;

	tmp = malloc(sizeof(*tmp));
	if (!tmp)
		return (FAILED_ALLOCATE);
	ret = g_class_cylinder.init(tmp);
	if (ret)
		return (free(tmp), ret);
	s = *str;
	ret = take_vec3d(&s, &tmp->__parent.coordinates);
	if (ret)
		return (tmp->__class->del(tmp), free(tmp), ret);
	ret = take_blank(&s);
	if (ret)
		return (tmp->__class->del(tmp), free(tmp), ret);
	ret = take_norm_vec3d(&s, &tmp->axis);
	if (ret)
		return (tmp->__class->del(tmp), free(tmp), ret);
	ret = take_blank(&s);
	if (ret)
		return (tmp->__class->del(tmp), free(tmp), ret);
	return (take_cylinder2(str, scene, s, tmp));
}

static inline int	take_cylinder2(char **str, t_scene *scene, char *s,
		t_cylinder *tmp)
{
	int	ret;

	ret = take_decimal(&s, &tmp->diameter);
	if (ret)
		return (tmp->__class->del(tmp), free(tmp), ret);
	ret = take_blank(&s);
	if (ret)
		return (tmp->__class->del(tmp), free(tmp), ret);
	ret = take_decimal(&s, &tmp->height);
	if (ret)
		return (tmp->__class->del(tmp), free(tmp), ret);
	ret = take_figure_optional(&s, (t_figure *)tmp);
	if (ret)
		return (tmp->__class->del(tmp), free(tmp), ret);
	ret = scene->__class->add_figure(scene, (t_figure *)tmp);
	if (ret)
		return (tmp->__class->del(tmp), free(tmp), FAILED_ALLOCATE);
	*str = s;
	return (NO_ERROR);
}
