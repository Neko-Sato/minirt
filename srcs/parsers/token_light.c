/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_light.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 00:19:40 by hshimizu          #+#    #+#             */
/*   Updated: 2024/06/04 00:47:44 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects/light.h"
#include "parser.h"
#include "rt_errno.h"
#include <stdlib.h>

static inline int	take_light2(char **str, t_scene *scene, char *s,
						t_light *tmp);

int	take_light(char **str, t_scene *scene)
{
	int		ret;
	char	*s;
	t_light	*tmp;

	tmp = malloc(sizeof(*tmp));
	if (!tmp)
		return (FAILED_ALLOCATE);
	ret = g_class_light.init(tmp);
	if (ret)
		return (free(tmp), ret);
	s = *str;
	ret = take_vec3d(&s, &tmp->coordinates);
	if (ret)
		return (tmp->__class->del(tmp), free(tmp), ret);
	ret = take_blank(&s);
	if (ret)
		return (tmp->__class->del(tmp), free(tmp), ret);
	ret = take_rate(&s, &tmp->brightness);
	if (ret)
		return (tmp->__class->del(tmp), free(tmp), ret);
	ret = take_blank(&s);
	if (ret)
		return (tmp->__class->del(tmp), free(tmp), ret);
	return (take_light2(str, scene, s, tmp));
}

static inline int	take_light2(char **str, t_scene *scene, char *s,
		t_light *tmp)
{
	int	ret;

	ret = take_color(&s, &tmp->color);
	if (ret)
		return (tmp->__class->del(tmp), free(tmp), ret);
	ret = scene->__class->add_light(scene, tmp);
	if (ret)
		return (tmp->__class->del(tmp), free(tmp), FAILED_ALLOCATE);
	*str = s;
	return (NO_ERROR);
}
