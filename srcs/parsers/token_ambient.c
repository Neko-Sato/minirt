/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_ambient.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 16:21:28 by hshimizu          #+#    #+#             */
/*   Updated: 2024/06/04 00:32:14 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects/ambient.h"
#include "parser.h"
#include "rt_errno.h"
#include <stdlib.h>

int	take_ambient(char **str, t_scene *scene)
{
	int			ret;
	char		*s;
	t_ambient	*tmp;

	tmp = malloc(sizeof(*tmp));
	if (!tmp)
		return (FAILED_ALLOCATE);
	ret = g_class_ambient.init(tmp);
	if (ret)
		return (free(tmp), ret);
	s = *str;
	ret = take_rate(&s, &tmp->ratio);
	if (ret)
		return (tmp->__class->del(tmp), free(tmp), ret);
	ret = take_blank(&s);
	if (ret)
		return (tmp->__class->del(tmp), free(tmp), ret);
	ret = take_color(&s, &tmp->color);
	if (ret)
		return (tmp->__class->del(tmp), free(tmp), ret);
	ret = scene->__class->set_ambient(scene, tmp);
	if (ret)
		return (tmp->__class->del(tmp), free(tmp), ret);
	*str = s;
	return (NO_ERROR);
}
