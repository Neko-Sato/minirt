/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_sphere.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 00:30:09 by hshimizu          #+#    #+#             */
/*   Updated: 2024/06/04 00:57:49 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects/sphere.h"
#include "parser.h"
#include "rt_errno.h"
#include <stdlib.h>

static inline int	take_sphere2(char **str, t_scene *scene, char *s,
						t_sphere *tmp);

int	take_sphere(char **str, t_scene *scene)
{
	int			ret;
	char		*s;
	t_sphere	*tmp;

	tmp = malloc(sizeof(*tmp));
	if (!tmp)
		return (FAILED_ALLOCATE);
	ret = g_class_sphere.init(tmp);
	if (ret)
		return (free(tmp), ret);
	s = *str;
	ret = take_vec3d(&s, &tmp->__parent.coordinates);
	if (ret)
		return (tmp->__class->del(tmp), free(tmp), ret);
	ret = take_blank(&s);
	if (ret)
		return (tmp->__class->del(tmp), free(tmp), ret);
	ret = take_decimal(&s, &tmp->diameter);
	if (ret)
		return (tmp->__class->del(tmp), free(tmp), ret);
	ret = take_blank(&s);
	if (ret)
		return (tmp->__class->del(tmp), free(tmp), ret);
	return (take_sphere2(str, scene, s, tmp));
}

static inline int	take_sphere2(char **str, t_scene *scene, char *s,
		t_sphere *tmp)
{
	int	ret;

	ret = take_color(&s, &tmp->__parent.color);
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
