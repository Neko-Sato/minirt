/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_ambient.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 16:21:28 by hshimizu          #+#    #+#             */
/*   Updated: 2024/06/18 19:20:55 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects/ambient.h"
#include "parser.h"
#include "rt_errno.h"
#include <stdlib.h>

int	parse_ambient(char **str, t_scene *scene)
{
	int			ret;
	char		*s;
	t_ambient	*tmp;

	tmp = malloc(sizeof(*tmp));
	if (!tmp)
		return (FAILED_ALLOCATE);
	ret = ambient_init(tmp);
	if (ret)
		return (free(tmp), ret);
	s = *str;
	ret = parse_rate(&s, &tmp->ratio);
	if (ret)
		return (ambient_del(tmp), free(tmp), ret);
	ret = parse_blank(&s);
	if (ret)
		return (ambient_del(tmp), free(tmp), ret);
	ret = parse_color(&s, &tmp->color);
	if (ret)
		return (ambient_del(tmp), free(tmp), ret);
	ret = scene_add_ambient(scene, tmp);
	if (ret)
		return (ambient_del(tmp), free(tmp), ret);
	*str = s;
	return (NO_ERROR);
}
